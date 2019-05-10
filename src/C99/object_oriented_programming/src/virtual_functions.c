#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Base Base;

typedef struct
{
	void (*virtual_function)(Base*);
	void (*virtual_destructor)(Base*);
} VirtualTable;

struct Base
{
	VirtualTable* vtable;
	int number;
};

void base_virtual_function(Base* b)
{
	printf("base_virtual_function: %i\n", b->number);
}

void base_virtual_destructor(Base* b)
{
	printf("base_virtual_destructor\n");
}

VirtualTable* base_viritual_table_factory()
{
	static VirtualTable vtable = {NULL, NULL};
	if (vtable.virtual_function != NULL && vtable.virtual_destructor != NULL)
		return &vtable;
	
	vtable.virtual_function = &base_virtual_function;
	vtable.virtual_destructor = &base_virtual_destructor;
	return &vtable;
}

Base* base_factory()
{
	static Base base;
	if (base.vtable != NULL)
		return &base;

	base.vtable = base_viritual_table_factory();
	base.number = 7;
	return &base;
}

typedef struct 
{
	Base base;
	char* str;
} Derived;

void derived_virtual_function(Base* base)
{
	Derived* derived = (Derived*)base;
	printf("derived_virtual_function: %i, %s\n", derived->base.number, derived->str);
}

void derived_virtual_destructor(Base* base)
{
	Derived* derived = (Derived*)base;
	free(derived->str);
	derived->str = NULL;
	printf("derived_virtual_destructor\n");
}

VirtualTable* derived_virtual_table_factory()
{
	static VirtualTable vtable;
	if (vtable.virtual_function != NULL && vtable.virtual_destructor != NULL)
		return &vtable;

	vtable.virtual_function = &derived_virtual_function;
	vtable.virtual_destructor = &derived_virtual_destructor;
	return &vtable;
}

Base* derived_factory()
{
	static Derived derived;
	if (derived.str != NULL)
		return &derived.base;

	derived.base.vtable = derived_virtual_table_factory();
	derived.base.number = 8;
	derived.str = (char*)malloc(strlen("foo") + 1);
	strcpy(derived.str, "foo");
	return &derived.base;
}

int main(void)
{
	Base* b1 = base_factory();
	b1->vtable->virtual_function(b1);
	b1->vtable->virtual_destructor(b1);
	
	Base* b2 = derived_factory();
	b2->vtable->virtual_function(b2);
	b2->vtable->virtual_destructor(b2);
}
