#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <locale.h>


int 	main()
{
	setlocale(LC_ALL, "");
	/*ft_printf("a%Sc%S\n", L"A", L"H");
	ft_printf("a%Sc%S\n", L"我", L"猫");
	ft_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S\n",
			  L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
			  L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	ft_printf("a%S", L"\x50\n");
	ft_printf("a%S\n", L"\xF0\x90\x8D\x86");
	printf("a%S\n", L"\xF0\x90\x8D\x86");
	ft_printf("% h\n");
	ft_printf("FLoat and integer: %20.15f\n%- 10.5i\n", 56.4131, 999);
	ft_printf("%-10.5o\n", 2500);
	printf("%-10.5o\n", 2500);*/

	/*ft_printf("%o\n", LONG_MIN);
	ft_printf("%lo\n", LONG_MIN);
	printf("%lo\n", LONG_MIN);
	printf("%O\n", LONG_MIN);*/

	ft_printf("%05C\n", 0);
	printf("%05C", 0);
	//ft_printf("% hZ%");
	//ft_printf("%x\n", -42);
	//printf("%x", -42);
}