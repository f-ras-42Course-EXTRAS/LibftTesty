/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testprog.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fras <fras@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/31 12:44:58 by fras          #+#    #+#                 */
/*   Updated: 2022/10/26 09:19:55 by fras          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define _STR			1
#define _ARR			2
#define _BOTH			3
#define _VAL			4

#define _GREEN			"\e[0;32m"
#define _RED			"\e[0;31m"
#define _COLOR_RESET	"\e[0m"


int	test(void *input1, void *input2, int len, int testnum, int mode);
int	simple_test(int input1, int input2, int testnum);
int  zero_neg_pos_test(int input1, int input2, int testnum);
int	ResultCheck(int *TestResultCount, int *LastCount);
char	*TestResultMsg(int result);
void	ProjectResultMsg(int ac, char *candidate, int result);
void	ResetStringsNArrays(char *s1, char *s2, const char *orgs,\
							long *a1, long *a2, const long *orga, int mode);
void	ResetDoublePointer(void *p1, void *p2);
void	StartCountdown (int countdowntimer);

int	g_speedmode = 0;

int		main(int argc, char *argv[])
{
	const char orgs[] = "Hello[zero this out] welcome to Codam.";
	char str1[] = "Hello[zero this out] welcome to Codam.";
	char str2[] = "Hello[zero this out] welcome to Codam.";

	char rtn1[64];
	char rtn2[64];
	
	const long orga[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
						57, 123, -4875769, 111, 222, 333};
	long arr1[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
						57, 123, -4875769, 111, 222, 333};
	long arr2[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
						57, 123, -4875769, 111, 222, 333};
	
	long rtn3[32] = {0};
	long rtn4[32] = {0};

	unsigned char arr3[256];
	signed char   arr4[256];
	char          rtn5[256];
	char          rtn6[256];

	int arr5[7] = {0, 6, 1, -1, 444, 7, 57};

	size_t				rtn7;
	size_t				rtn8;
	
	char empty_str[] = "";

	char orgsx[27 + 39] = "Let's concatenate!!!!!!!: ";
	char str3[27 + 39] = "Let's concatenate!!!!!!!: ";
	char str4[27 + 39] = "Let's concatenate!!!!!!!: ";

	size_t	*ptr1;
	char	*ptr2;
	char	*ptr3;
	int	testerror = 0;
	
	char candidate[32];

	int TestResultCount = 0;
	int LastCount = 0;
	int check = 0;
	int t = 0;
	int countdowntimer = 10;

	if (argc == 2 && strcmp(argv[1], "SPEEDMODE") == 0)
	{
		g_speedmode = 1;
		argc = 1;
	}
	if (argc == 2)
		strcpy(candidate, argv[1]);


	#define FCNAME "TEST PROGRAM"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	printf("Testprogram: "); TestResultCount += test(str1, str2, 0, t++, _STR);	
	printf("\n%s\n%s\n\n", str1, str2);                  					        //test start
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (check != 0)
	  return(0);
	StartCountdown(countdowntimer);
	printf("\n\n");
	
	#define FCNAME "ft_memset.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	strncpy(rtn1, memset(str1 + 5, '0', 15 * (sizeof(char))), sizeof(orgs));      	//function call + save return
	strncpy(rtn2, ft_memset(str2 + 5, '0', 15 * (sizeof(char))), sizeof(orgs));   	//function call	+ save return
	TestResultCount += test(rtn1, rtn2, 0, t++, _STR);                         		//test return value
	TestResultCount += test(str1, str2, 0, t++, _STR);						        //test after call
	printf("\n%s\n%s\n", str1, str2);
	printf("\n%s\n%s\n", rtn1, rtn2);
	memset(arr1, -1, sizeof(orga));
	ft_memset(arr2, -1, sizeof(orga));
	TestResultCount += test(arr1, arr2, sizeof(orga), t++, _ARR);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _BOTH);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_bzero.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	bzero(str1 + 5, 15 * (sizeof(char)));
	ft_bzero(str2 + 5, 15 * (sizeof(char)));
	TestResultCount += test(str1, str2, 0, t++, _STR);
	TestResultCount += test(str1 + 19, str2 + 19, 0, t++, _STR);
	TestResultCount += test(str1 + 20, str2 + 20, 0, t++, _STR);
	printf("\nAfter call:\n{\"%s\"}\n{\"%s\"}\n", str1, str2);
	printf("\n'(str + 19)':\n{\"%s\"}\n{\"%s\"}\n", str1 + 19, str2 + 19);
	printf("\n'(str + 20)':\n{\"%s\"}\n{\"%s\"}\n\n", str1 + 20, str2 + 20);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _STR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_memcpy.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	printf("\n%s\n%s\n\n", str1, str2);
	memcpy(rtn3, memcpy(arr1 + 9, orga, 3 * sizeof(long)), 3 * sizeof(long));
	memcpy(rtn4, ft_memcpy(arr2 + 9, orga, 3 * sizeof(long)), 3 * sizeof(long));
	TestResultCount += test(arr1, arr2, sizeof(orga), t++, _ARR);
	TestResultCount += test(rtn3, rtn4, sizeof(rtn3), t++, _ARR);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _ARR);
	memcpy(arr1 + 9, arr1, 3 * sizeof(long));
	ft_memcpy(arr2 + 9, arr2, 3 * sizeof(long));
	TestResultCount += test(arr1, arr2, sizeof(orga), t++, _ARR);
	strncpy(rtn1, memcpy(str1 + 20, orgs + 5, 15), sizeof(orgs));
	strncpy(rtn2, ft_memcpy(str2 + 20, orgs + 5, 15), sizeof(orgs));
	TestResultCount += test(str1, str2, sizeof(orgs), t++, _ARR);
	TestResultCount += test(rtn1, rtn2, sizeof(orgs), t++, _ARR);
	for(int i = 0; i < 12; i++)
		printf("%ld, ", arr1[i]);
	putchar('\n');
	for(int i = 0; i < 12; i++)
		printf("%ld, ", arr2[i]);
	putchar('\n');
	for(int i = 0; i < 20; i++)
		printf("%ld, ", rtn3[i]);
	putchar('\n');
	for(int i = 0; i < 20; i++)
		printf("%ld, ", rtn4[i]);
	printf("\n%s\n%s\n", rtn1, rtn2);
	printf("\n%s\n%s\n", str1, str2);
	for(int i = 0; i < 39; i++)
		printf("%c", str1[i]);
	printf("\n");
	for(int i = 0; i < 39; i++)
		printf("%c", str2[i]);
	printf("\n");
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _BOTH);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_isalpha.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	for (int i = 0; i <= 255; i++)
	{
		arr3[i] = i;
		arr4[i] = i - 128;
	}
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isalpha(arr3[i]);
		rtn6[i] = ft_isalpha(arr3[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr3), t++, _ARR);
	printf("\n\n");
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isalpha(arr4[i]);
		rtn6[i] = ft_isalpha(arr4[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr4), t++, _ARR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_isdigit.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	for (int i = 0; i <= 255; i++)
	{
		arr3[i] = i;
		arr4[i] = i - 128;
	}
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isdigit(arr3[i]);
		rtn6[i] = ft_isdigit(arr3[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr3), t++, _ARR);
	printf("\n\n");
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isdigit(arr4[i]);
		rtn6[i] = ft_isdigit(arr4[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr4), t++, _ARR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_isalnum.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	for (int i = 0; i <= 255; i++)
	{
		arr3[i] = i;
		arr4[i] = i - 128;
	}
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isalnum(arr3[i]);
		rtn6[i] = ft_isalnum(arr3[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr3), t++, _ARR);
	printf("\n\n");
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isalnum(arr4[i]);
		rtn6[i] = ft_isalnum(arr4[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr4), t++, _ARR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);
	
	#define FCNAME "ft_isascii.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	for (int i = 0; i <= 255; i++)
	{
		arr3[i] = i;
		arr4[i] = i - 128;
	}
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isascii(arr3[i]);
		rtn6[i] = ft_isascii(arr3[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr3), t++, _ARR);
	printf("\n\n");
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isascii(arr4[i]);
		rtn6[i] = ft_isascii(arr4[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr4), t++, _ARR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);
	
	#define FCNAME "ft_isprint.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	for (int i = 0; i <= 255; i++)
	{
		arr3[i] = i;
		arr4[i] = i - 128;
	}
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isprint(arr3[i]);
		rtn6[i] = ft_isprint(arr3[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr3), t++, _ARR);
	printf("\n\n");
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = isprint(arr4[i]);
		rtn6[i] = ft_isprint(arr4[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%d:%d - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr4), t++, _ARR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);
	
	#define FCNAME "ft_strlen.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += simple_test(strlen(orgs), ft_strlen(orgs), t++);
	TestResultCount += simple_test(strlen(empty_str), ft_strlen(empty_str), t++);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	#define FCNAME "ft_memmove.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _BOTH);
	printf("\n%s\n%s\n\n", str1, str2);
	memcpy(rtn3, memmove(arr1 + 9, orga, 3 * sizeof(long)), 3 * sizeof(long));
	memcpy(rtn4, ft_memmove(arr2 + 9, orga, 3 * sizeof(long)), 3 * sizeof(long));
	for(int i = 0; i < 12; i++)
		printf("%ld, ", arr1[i]);
	putchar('\n');
	for(int i = 0; i < 12; i++)
		printf("%ld, ", arr2[i]);
	putchar('\n');
	TestResultCount += test(arr1, arr2, sizeof(orga), t++, _ARR);
	TestResultCount += test(rtn3, rtn4, sizeof(rtn3), t++, _ARR);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _ARR);
	memmove(arr1 + 9, arr1, 3 * sizeof(long));
	ft_memmove(arr2 + 9, arr2, 3 * sizeof(long));
	TestResultCount += test(arr1, arr2, sizeof(orga), t++, _ARR);
	strncpy(rtn1, memmove(str1 + 20, orgs + 5, 15), sizeof(orgs));
	strncpy(rtn2, ft_memmove(str2 + 20, orgs + 5, 15), sizeof(orgs));
	TestResultCount += test(str1, str2, sizeof(orgs), t++, _ARR);
	TestResultCount += test(rtn1, rtn2, sizeof(orgs), t++, _ARR);
	for(int i = 0; i < 12; i++)
		printf("%ld, ", arr1[i]);
	putchar('\n');
	for(int i = 0; i < 12; i++)
		printf("%ld, ", arr2[i]);
	putchar('\n');
	for(int i = 0; i < 20; i++)
		printf("%ld, ", rtn3[i]);
	putchar('\n');
	for(int i = 0; i < 20; i++)
		printf("%ld, ", rtn4[i]);
	printf("\n%s\n%s\n", rtn1, rtn2);
	printf("\n%s\n%s\n", str1, str2);
	for(int i = 0; i < 39; i++)
		printf("%c", str1[i]);
	printf("\n");
	for(int i = 0; i < 39; i++)
		printf("%c", str2[i]);
	printf("\n");
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _BOTH);
	printf("\n%s\n%s\n\n", str1, str2);								//- Overlapping mem-area
	strcpy(rtn1, memmove(str1 + 5, str1, 15));
	strcpy(rtn2, ft_memmove(str2 + 5, str2, 15));
	TestResultCount += test(str1, str2, 0, t++, _STR);
	TestResultCount += test(rtn1, rtn2, 0, t++, _STR);
	printf("\n%s\n%s\n", str1, str2);
	printf("%s\n%s\n", rtn1, rtn2);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _STR);
	strcpy(rtn1, memmove(str1, str1 + 5, 15));
	strcpy(rtn2, ft_memmove(str2, str2 + 5, 15));
	TestResultCount += test(str1, str2, 0, t++, _STR);
	TestResultCount += test(rtn1, rtn2, 0, t++, _STR);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _STR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strlcpy.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	rtn7 = strlcpy(str1 + 5, orgs, 15);
	rtn8 = ft_strlcpy(str2 + 5, orgs, 15);
	TestResultCount += test(str1, str2, 0, t++, _STR);
	TestResultCount += simple_test(rtn7, rtn8, t++);
	printf("\n%s\n%s\n", str1, str2);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _STR);
	rtn7 = strlcpy(str1, empty_str, sizeof(str1));
	rtn8 = ft_strlcpy(str2, empty_str, sizeof(str2));
	TestResultCount += test(str1, str2, 0, t++, _STR);
	TestResultCount += simple_test(rtn7, rtn8, t++);
	ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _STR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strlcat.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	rtn7 = strlcat(str3, str1, sizeof(str3));
	rtn8 = ft_strlcat(str4, str2, sizeof(str4));
	TestResultCount += test(str3, str4, 0, t++, _STR);
	TestResultCount += simple_test(rtn7, rtn8, t++);
	printf("1: \n%s\n%s\n", str3, str4);
	printf("1: \n%lu-%lu\n\n", rtn7, rtn8);
	ResetStringsNArrays(str3, str4, orgsx, arr1, arr2, orga, _STR);
	rtn7 = strlcat(str3, str1, (sizeof(str3) - 30));
	rtn8 = ft_strlcat(str4, str2, (sizeof(str4) - 30));
	TestResultCount += test(str3, str4, 0, t++, _STR);
	TestResultCount += simple_test(rtn7, rtn8, t++);
	printf("2: \n%s\n%s\n", str3, str4);
	printf("2: \n%lu-%lu\n\n", rtn7, rtn8);
	ResetStringsNArrays(str3, str4, orgsx, arr1, arr2, orga, _STR);
	rtn7 = strlcat(str3, empty_str, sizeof(str3));
	rtn8 = ft_strlcat(str4, empty_str, sizeof(str4));
	TestResultCount += test(str3, str4, 0, t++, _STR);
	TestResultCount += simple_test(rtn7, rtn8, t++);
	printf("3: \n%s\n%s\n", str3, str4);
	printf("3: \n%lu-%lu\n", rtn7, rtn8);
	ResetStringsNArrays(str3, str4, orgsx, arr1, arr2, orga, _STR);
	rtn7 = strlcat(empty_str, str3, 1);
	rtn8 = ft_strlcat(empty_str, str4, 1);
	TestResultCount += test(empty_str, empty_str, 0, t++, _STR);
	TestResultCount += simple_test(rtn7, rtn8, t++);
	printf("4: \n%s\n%s\n", empty_str, empty_str);
	printf("4: \n%lu-%lu\n", rtn7, rtn8);
	ResetStringsNArrays(str3, str4, orgsx, arr1, arr2, orga, _STR);
	rtn7 = strlcat(str3, str1, 0);
	rtn8 = ft_strlcat(str4, str2, 0);
	TestResultCount += test(str3, str4, 0, t++, _STR);
	TestResultCount += simple_test(rtn7, rtn8, t++);
	printf("5: \n%s\n%s\n", str3, str4);
	printf("5: \n%lu-%lu\n\n", rtn7, rtn8);
	ResetStringsNArrays(str3, str4, orgsx, arr1, arr2, orga, _STR);
	rtn7 = strlcat(str3, str1, 10);
	rtn8 = ft_strlcat(str4, str2, 10);
	TestResultCount += test(str3, str4, 0, t++, _STR);
	TestResultCount += simple_test(rtn7, rtn8, t++);
	printf("6: \n%s\n%s\n", str3, str4);
	printf("6: \n%lu-%lu\n\n", rtn7, rtn8);
	ResetStringsNArrays(str3, str4, orgsx, arr1, arr2, orga, _STR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_toupper.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	for (int i = 0; i <= 255; i++)
	{
		arr3[i] = i;
		arr4[i] = i - 128;
	}
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = toupper(arr3[i]);
		rtn6[i] = ft_toupper(arr3[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%c:%c - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr3), t++, _ARR);
	printf("\n\n");
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = toupper(arr4[i]);
		rtn6[i] = ft_toupper(arr4[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%c:%c - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr4), t++, _ARR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_tolower.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	for (int i = 0; i <= 255; i++)
	{
		arr3[i] = i;
		arr4[i] = i - 128;
	}
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = tolower(arr3[i]);
		rtn6[i] = ft_tolower(arr3[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%c:%c - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr3), t++, _ARR);
	printf("\n\n");
	for (int i = 0; i <= 255; i++)
	{
		rtn5[i] = tolower(arr4[i]);
		rtn6[i] = ft_tolower(arr4[i]);
	}
	for (int i = 0; i <= 255; i++)
		printf("%c:%c - ", rtn5[i], rtn6[i]);
	printf("\n\n");
	TestResultCount += test(rtn5, rtn6, sizeof(arr4), t++, _ARR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strchr.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += test(strchr(str1, 'x'), ft_strchr(str1, 'x'), 0, t++, \
	 _VAL);
	TestResultCount += test(strchr(str1, 'e'), ft_strchr(str1, 'e'), 0, t++, \
	_STR);
	TestResultCount += test(strchr(str1, 357), ft_strchr(str1, 357), 0, t++, \
		_STR);
	TestResultCount += test(strchr(str1, '\0'), ft_strchr(str1, '\0'), 0, t++, \
	_VAL);
	TestResultCount +=\
	 test(strchr("1\000\0002", 2), ft_strchr("1\000\0002", 2),\
	  0, t++,  _VAL);
	printf("%s || %s\n", strchr(str1, 'x'), ft_strchr(str1, 'x'));
	printf("%p || %p\n", strchr(str1, 'x'), ft_strchr(str1, 'x'));
	printf("%s || %s\n", strchr(str1, 'e'), ft_strchr(str1, 'e'));
	printf("%s || %s\n", strchr(str1, 357), ft_strchr(str1, 357));
	printf("%s || %s\n", strchr(str1, '\0'), ft_strchr(str1, '\0'));
	printf("%p || %p\n", strchr(str1, '\0'), ft_strchr(str1, '\0'));
	printf("%s || %s\n",\
	 strchr("1\000\0002", '2'), ft_strchr("1\000\0002", '2'));
	printf("%p || %p\n",\
	 strchr("1\000\0002", '2'), ft_strchr("1\000\0002", '2'));
	check = ResultCheck(&TestResultCount, &LastCount);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strrchr.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += test(strrchr(str1, 'x'), ft_strrchr(str1, 'x'), 0, t++, \
	 _VAL);
	TestResultCount += test(strrchr(str1, 'e'), ft_strrchr(str1, 'e'), 0, t++, \
	_STR);
	TestResultCount += test(strrchr(str1, 357), ft_strrchr(str1, 357), 0, t++, \
	_STR);
	TestResultCount += test(strrchr(str1, '\0'), ft_strrchr(str1, '\0'), 0, t++, \
	_VAL);
	TestResultCount +=\
	 test(strrchr("1\000\0002", 2), ft_strrchr("1\000\0002", 2),\
	  0, t++,  _VAL);
	printf("%s || %s\n", strrchr(str1, 'x'), ft_strrchr(str1, 'x'));
	printf("%p || %p\n", strrchr(str1, 'x'), ft_strrchr(str1, 'x'));
	printf("%s || %s\n", strrchr(str1, 'e'), ft_strrchr(str1, 'e'));
	printf("%s || %s\n", strrchr(str1, 357), ft_strrchr(str1, 357));
	printf("%s || %s\n", strrchr(str1, '\0'), ft_strrchr(str1, '\0'));
	printf("%p || %p\n", strrchr(str1, '\0'), ft_strrchr(str1, '\0'));
	printf("%s || %s\n",\
	 strrchr("1\000\0002", '2'), ft_strrchr("1\000\0002", '2'));
	printf("%p || %p\n",\
	 strrchr("1\000\0002", '2'), ft_strrchr("1\000\0002", '2'));
	check = ResultCheck(&TestResultCount, &LastCount);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strncmp.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += zero_neg_pos_test(strncmp(str1, str2, sizeof(str1)), ft_strncmp(str1, str2, sizeof(str1)), t++);
	printf("[%d] - [%d]\n", strncmp(str1, str2, sizeof(str1)), ft_strncmp(str1, str2, sizeof(str1)));
	TestResultCount += zero_neg_pos_test(strncmp("hello", "helli", 6), ft_strncmp("hello", "helli", 6), t++);
	printf("[%d] - [%d]\n", strncmp("hello", "helli", 6), ft_strncmp("hello", "helli", 6));
	TestResultCount += zero_neg_pos_test(strncmp("hello", "hellx", 6), ft_strncmp("hello", "hellx", 6), t++);
	printf("[%d] - [%d]\n", strncmp("hello", "hellx", 6), ft_strncmp("hello", "hellx", 6));
	TestResultCount += zero_neg_pos_test(strncmp("hello", "hellx", 4), ft_strncmp("hello", "hellx", 4), t++);
	printf("[%d] - [%d]\n", strncmp("hello", "hellx", 4), ft_strncmp("hello", "hellx", 4));
	TestResultCount += zero_neg_pos_test(strncmp("hello", "hellx", 5), ft_strncmp("hello", "hellx", 5), t++);
	printf("[%d] - [%d]\n", strncmp("hello", "hellx", 5), ft_strncmp("hello", "hellx", 5));
	TestResultCount += zero_neg_pos_test(strncmp("hello", "hellx", 0), ft_strncmp("hello", "hellx", 0), t++);
	printf("[%d] - [%d]\n", strncmp("hello", "hellx", 0), ft_strncmp("hello", "hellx", 0));
	TestResultCount += zero_neg_pos_test(strncmp("hello", "uellx", 1), ft_strncmp("hello", "uellx", 1), t++);
	printf("[%d] - [%d]\n", strncmp("hello", "uellx", 1), ft_strncmp("hello", "uellx", 1));
	TestResultCount += zero_neg_pos_test(strncmp("a", "", 10), ft_strncmp("a", "", 10), t++);
	printf("[%d] - [%d]\n", strncmp("a", "", 10), ft_strncmp("a", "", 10));
	TestResultCount += zero_neg_pos_test(strncmp("a\000b", "a\000c", 4), ft_strncmp("a\000b", "a\000c", 4), t++);
	printf("[%d] - [%d]\n", strncmp("a\000b", "a\000c", 4), ft_strncmp("a\000b", "a\000c", 4));
	TestResultCount += zero_neg_pos_test(strncmp("a\200b", "a\001c", 4), ft_strncmp("a\200b", "a\001c", 4), t++);
	printf("[%d] - [%d]\n", strncmp("a\200b", "a\001c", 4), ft_strncmp("a\200b", "a\001c", 4));
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_memchr.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount +=\
	 test(memchr(str1, 'x', sizeof(str1)), ft_memchr(str1, 'x', sizeof(str1)),\
	  0, t++,  _VAL);
	TestResultCount +=\
	 test(memchr(str1, 'e', sizeof(str1)), ft_memchr(str1, 'e', sizeof(str1)),\
	  0, t++,  _STR);
	TestResultCount +=\
	 test(memchr(str1, '\0', sizeof(str1)), ft_memchr(str1, '\0', sizeof(str1)),\
	  0, t++,  _VAL);
	TestResultCount +=\
	 test(memchr("1\000\0002", 2, 5), ft_memchr("1\000\0002", 2, 5),\
	  0, t++,  _VAL);
	TestResultCount +=\
	 test(memchr("1\000\0002", 4, 5), ft_memchr("1\000\0002", 4, 5),\
	  0, t++,  _VAL);
	TestResultCount +=\
	 test(memchr("1\200\0002", 128, 5), ft_memchr("1\200\0002", 128, 5),\
	  0, t++,  _VAL); 
	TestResultCount +=\
	 test(memchr("1\200\0002", '\200', 5), ft_memchr("1\200\0002", '\200', 5),\
	  0, t++,  _VAL);
	TestResultCount +=\
	 test(memchr(arr5, -1, sizeof(arr5)), ft_memchr(arr5, -1, sizeof(arr5)),\
	  sizeof(arr5), t++,  _VAL);
	TestResultCount +=\
	 test(memchr(str1, 'l', 2), ft_memchr(str1, 'l', 2),\
	  0, t++,  _VAL);
	TestResultCount +=\
	 test(memchr("", '[', 0), ft_memchr("", '[', 0),\
	  0, t++,  _VAL);
	TestResultCount +=\
	 test(memchr(str1, 'h', 0), ft_memchr(str1, 'h', 0),\
	  0, t++,  _VAL);
	memchr(arr5, -1, sizeof(arr5));
	printf("%s || %s\n",\
	 memchr(str1, 'x', sizeof(str1)), ft_memchr(str1, 'x', sizeof(str1)));
	printf("%p || %p\n",\
	 memchr(str1, 'x', sizeof(str1)), ft_memchr(str1, 'x', sizeof(str1)));
	printf("%s || %s\n",\
	 memchr(str1, 'e', sizeof(str1)), ft_memchr(str1, 'e', sizeof(str1)));
	printf("%s || %s\n",\
	 memchr(str1, '\0', sizeof(str1)), ft_memchr(str1, '\0', sizeof(str1)));
	printf("%p || %p\n",\
	 memchr(str1, '\0', sizeof(str1)), ft_memchr(str1, '\0', sizeof(str1)));
	printf("%s || %s\n",\
	 memchr("1\000\0002", '2', 5), ft_memchr("1\000\0002", '2', 5));
	printf("%p || %p\n",\
	 memchr("1\000\0002", '2', 5), ft_memchr("1\000\0002", '2', 5));
	printf("%s || %s\n",\
	 memchr("1\000\0002", '4', 5), ft_memchr("1\000\0002", '4', 5));
	printf("%p || %p\n",\
	 memchr("1\000\0002", '4', 5), ft_memchr("1\000\0002", '4', 5));
	printf("%p || %p\n",\
	 memchr("1\200\0002", 128, 5), ft_memchr("1\200\0002", 128, 5));
	printf("%p || %p\n",\
	 memchr("1\200\0002", '\200', 5), ft_memchr("1\200\0002", '\200', 5));
	printf("%p || %p\n",\
	 memchr(arr5, -1, sizeof(arr5)), ft_memchr(arr5, -1, sizeof(arr5)));
	printf("%s || %s\n",\
	 memchr(str1, 'l', 2), ft_memchr(str1, 'l', 2));
	printf("%p || %p\n",\
	 memchr("", 'l', 0), ft_memchr("", 'l', 0));
	printf("%p || %p\n",\
	 memchr(str1, 'h', 0), ft_memchr(str1, 'h', 0));
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_memcmp.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += zero_neg_pos_test(memcmp(str1, str2, sizeof(str1)), ft_memcmp(str1, str2, sizeof(str1)), t++);
	printf("[%d] - [%d]\n", memcmp(str1, str2, sizeof(str1)), ft_memcmp(str1, str2, sizeof(str1)));
	TestResultCount += zero_neg_pos_test(memcmp("hello", "helli", 6), ft_memcmp("hello", "helli", 6), t++);
	printf("[%d] - [%d]\n", memcmp("hello", "helli", 6), ft_memcmp("hello", "helli", 6));
	TestResultCount += zero_neg_pos_test(memcmp("hello", "hellx", 6), ft_memcmp("hello", "hellx", 6), t++);
	printf("[%d] - [%d]\n", memcmp("hello", "hellx", 6), ft_memcmp("hello", "hellx", 6));
	TestResultCount += zero_neg_pos_test(memcmp("hello", "hellx", 4), ft_memcmp("hello", "hellx", 4), t++);
	printf("[%d] - [%d]\n", memcmp("hello", "hellx", 4), ft_memcmp("hello", "hellx", 4));
	TestResultCount += zero_neg_pos_test(memcmp("hello", "hellx", 5), ft_memcmp("hello", "hellx", 5), t++);
	printf("[%d] - [%d]\n", memcmp("hello", "hellx", 5), ft_memcmp("hello", "hellx", 5));
	TestResultCount += zero_neg_pos_test(memcmp("hello", "hellx", 0), ft_memcmp("hello", "hellx", 0), t++);
	printf("[%d] - [%d]\n", memcmp("hello", "hellx", 0), ft_memcmp("hello", "hellx", 0));
	TestResultCount += zero_neg_pos_test(memcmp("hello", "uellx", 1), ft_memcmp("hello", "uellx", 1), t++);
	printf("[%d] - [%d]\n", memcmp("hello", "uellx", 1), ft_memcmp("hello", "uellx", 1));
	TestResultCount += zero_neg_pos_test(memcmp("a", "", 10), ft_memcmp("a", "", 10), t++);
	printf("[%d] - [%d]\n", memcmp("a", "", 10), ft_memcmp("a", "", 10));
	TestResultCount += zero_neg_pos_test(memcmp("a\000b", "a\000c", 4), ft_memcmp("a\000b", "a\000c", 4), t++);
	printf("[%d] - [%d]\n", memcmp("a\000b", "a\000c", 4), ft_memcmp("a\000b", "a\000c", 4));
	TestResultCount += zero_neg_pos_test(memcmp(arr1, arr2, 4), ft_memcmp(arr1, arr2, 4), t++);
	printf("[%d] - [%d]\n", memcmp(arr1, arr2, sizeof(orga)), ft_memcmp(arr1, arr2, sizeof(orga)));
	arr2[2] = -2147483649;
	TestResultCount += zero_neg_pos_test(memcmp(arr1, arr2, sizeof(orga)), ft_memcmp(arr1, arr2, sizeof(orga)), t++);
	printf("[%d] - [%d]\n", memcmp(arr1, arr2, sizeof(orga)), ft_memcmp(arr1, arr2, sizeof(orga)));
	ResetStringsNArrays(str3, str4, orgsx, arr1, arr2, orga, _ARR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strnstr.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += test(strnstr(str1, "[zero this out]", sizeof(str1)),\
	 ft_strnstr(str1, "[zero this out]", sizeof(str1)), 0, t++, _STR);
	printf("OR: %s\nFT: %s\n", strnstr(str1, "[zero this out]", sizeof(str1)),\
	 ft_strnstr(str1, "[zero this out]", sizeof(str1)));
	TestResultCount += test(strnstr(str1, "", sizeof(str1)),\
	 ft_strnstr(str1, "", sizeof(str1)), 0, t++, _STR);
	printf("OR: %s\nFT: %s\n", strnstr(str1, "", sizeof(str1)),\
	 ft_strnstr(str1, "", sizeof(str1)));
	TestResultCount += test(strnstr("", "", sizeof(str1)),\
	 ft_strnstr("", "", sizeof(str1)), 0, t++, _VAL);
	printf("OR: %s\nFT: %s\n", strnstr("", "", sizeof(str1)),\
	 ft_strnstr("", "", sizeof(str1)));
	TestResultCount += test(strnstr("", str1, sizeof(str1)),\
	 ft_strnstr("", str1, sizeof(str1)), 0, t++, _VAL);
	printf("OR: %s\nFT: %s\n", strnstr("", str1, sizeof(str1)),\
	 ft_strnstr("", str1, sizeof(str1)));
	TestResultCount += test(strnstr(str1, "[zero this out]", sizeof(str1) - 20),\
	 ft_strnstr(str1, "[zero this out]", sizeof(str1) - 20), 0, t++, _VAL);
	printf("OR: %s\nFT: %s\n", strnstr(str1, "[zero this out]", sizeof(str1) - 20),\
	 ft_strnstr(str1, "[zero this out]", sizeof(str1) - 20));
	TestResultCount += test(strnstr(str1, "[zero this out]", sizeof(str1) - 19),\
	 ft_strnstr(str1, "[zero this out]", sizeof(str1) - 19), 0, t++, _VAL);
	printf("OR: %s\nFT: %s\n", strnstr(str1, "[zero this out]", sizeof(str1) - 19),\
	 ft_strnstr(str1, "[zero this out]", sizeof(str1) - 19));
	TestResultCount += test(strnstr(str1, "elc", sizeof(str1)),\
	 ft_strnstr(str1, "elc", sizeof(str1)), 0, t++, _VAL);
	printf("OR: %s\nFT: %s\n", strnstr(str1, "elc", sizeof(str1)),\
	 ft_strnstr(str1, "elc", sizeof(str1)));
	TestResultCount += test(strnstr(str1, str1, sizeof(str1) + 1),\
	 ft_strnstr(str1, str1, sizeof(str1) + 1), 0, t++, _VAL);
	printf("OR: %s\nFT: %s\n", strnstr(str1, str1, sizeof(str1) + 1),\
	 ft_strnstr(str1, str1, sizeof(str1) + 1));
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_atoi.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += simple_test(atoi("   1004"), ft_atoi("   1004"), t++);
	printf("%d | %d\n", atoi("   1004"), ft_atoi("   1004"));
	TestResultCount += simple_test(atoi("   004"), ft_atoi("   004"), t++);
	printf("%d | %d\n", atoi("   004"), ft_atoi("   004"));
	TestResultCount += simple_test(atoi("   -1004"), ft_atoi("   -1004"), t++);
	printf("%d | %d\n", atoi("   -1004"), ft_atoi("   -1004"));
	TestResultCount += simple_test(atoi("   -004"), ft_atoi("   -004"), t++);
	printf("%d | %d\n", atoi("   -004"), ft_atoi("   -004"));
	TestResultCount += simple_test(atoi("   +1004"), ft_atoi("   +1004"), t++);
	printf("%d | %d\n", atoi("   +1004"), ft_atoi("   +1004"));
	TestResultCount += simple_test(atoi("   +004"), ft_atoi("   +004"), t++);
	printf("%d | %d\n", atoi("   +004"), ft_atoi("   +004"));
	TestResultCount += simple_test(atoi("   ++1004"), ft_atoi("   ++1004"), t++);
	printf("%d | %d\n", atoi("   ++1004"), ft_atoi("   ++1004"));
	TestResultCount += simple_test(atoi("   ++004"), ft_atoi("   ++004"), t++);
	printf("%d | %d\n", atoi("   ++004"), ft_atoi("   ++004"));
	TestResultCount += simple_test(atoi("   --1004"), ft_atoi("   --1004"), t++);
	printf("%d | %d\n", atoi("   --1004"), ft_atoi("   --1004"));
	TestResultCount += simple_test(atoi("   --004"), ft_atoi("   --004"), t++);
	printf("%d | %d\n", atoi("   --004"), ft_atoi("   --004"));
	TestResultCount += simple_test(atoi("   0"), ft_atoi("   0"), t++);
	printf("%d | %d\n", atoi("   0"), ft_atoi("   0"));
	TestResultCount += simple_test(atoi(" \t\n\v\f\r -1004"), ft_atoi(" \t\n\v\f\r -1004"), t++);
	printf("%d | %d\n", atoi(" \t\n\v\f\r -1004"), ft_atoi(" \t\n\v\f\r -1004"));
	TestResultCount += simple_test(atoi("   +-4"), ft_atoi("   +-4"), t++);
	printf("%d | %d\n", atoi("   +-4"), ft_atoi("   +-4"));
	TestResultCount += simple_test(atoi("0"), ft_atoi("0"), t++);
	printf("%d | %d\n", atoi("0"), ft_atoi("0"));
	TestResultCount += simple_test(atoi(""), ft_atoi(""), t++);
	printf("%d | %d\n", atoi(""), ft_atoi(""));
	TestResultCount += simple_test(atoi("-2147483648"), ft_atoi("-2147483648"), t++);
	printf("%d | %d\n", atoi("-2147483648"), ft_atoi("-2147483648"));
	TestResultCount += simple_test(atoi("2147483647"), ft_atoi("2147483647"), t++);
	printf("%d | %d\n", atoi("2147483647"), ft_atoi("2147483647"));
	TestResultCount += simple_test(atoi("   \r -2147483649"), ft_atoi("   \r -2147483649"), t++);
	printf("%d | %d\n", atoi("   \r -2147483649"), ft_atoi("   \r -2147483649"));
	TestResultCount += simple_test(atoi("   -444 12"), ft_atoi("   -444 12"), t++);
	printf("%d | %d\n", atoi("   -444 12"), ft_atoi("   -444 12"));
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_calloc.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ptr1 = ft_calloc(444, sizeof(size_t));
	if (!ptr1)
	{
		TestResultCount += simple_test(1, 0, t++);
		testerror = 1;
	}
	else
		TestResultCount += simple_test(1, 1, t++);
	if (ptr1)
	{
		for (size_t i = 0; i < 444; i++)
		{
			if (ptr1[i] != 0)
			{
				testerror = 1;
				break;
			}
		}
	}
	if (testerror)
		TestResultCount += simple_test(1, 0, t++);
	else
		TestResultCount += simple_test(1, 1, t++);
	free(ptr1);
	ptr1 = NULL;
	testerror = 0;
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strdup.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ptr2 = ft_strdup(orgs);
	ptr3 = strdup(orgs);
	TestResultCount += test(ptr2, ptr3, 0, t++, _STR);
	ResetDoublePointer(ptr2, ptr3);
	ptr2 = ft_strdup("");
	ptr3 = strdup("");
	TestResultCount += test(ptr2, ptr3, 0, t++, _STR);
	ResetDoublePointer(ptr2, ptr3);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_substr.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	// ptr2 = ft_substr("", 0, 1);
	// TestResultCount += simple_test(*ptr2, '\0', t++);
	// printf("%d", *ptr2, 0);
	// free(ptr2);
	// ptr2 = NULL;
	ptr2 = ft_substr(orgs, 0, strlen(orgs));
	TestResultCount += test((char *)orgs, ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", orgs, ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("Hello there", 0, 10);
	TestResultCount += test("Hello ther", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "Hello ther" , ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("Test", 1, 4);
	TestResultCount += test("est", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "est", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("", 1, 4);
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("", 2, 4);
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("Hallo", 4, 3);
	TestResultCount += test("o", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "o", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("Hallo", 3, 3);
	TestResultCount += test("lo", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "lo", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("Hello there", 4, 4);
	TestResultCount += test("o th", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "o th", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr(orgs, 5, 15);
	TestResultCount += test("[zero this out]", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "[zero this out]", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("Hello", 5, 7);
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("Hello", 14, 7);
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("", 1, 1);
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("test minus", 0, -1);
	TestResultCount += test("test minus", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "test minus", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_substr("heya", 5, 2);
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));

	//--FINAL RESULTS--
	ProjectResultMsg(argc, candidate, TestResultCount);
	return(0);
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

int		test(void *input1, void *input2, int len, int testnum, int mode)
{
	if (mode == _STR)
	{
		if (!input1 || !input2)
			return (simple_test((int)input1, (int)input2, testnum));
		else if(strcmp(input1, input2) == 0)
		{
			printf(_GREEN "TEST%d VALID\n" _COLOR_RESET, testnum);
			if (!g_speedmode) usleep(0.075*1000000);
			return(0);
		}
		else
		{
			printf(_RED "TEST%d FAILED\n" _COLOR_RESET, testnum);	
			if (!g_speedmode) usleep(0.075*1000000);
			return(1);
		}
	}
	if(mode == _ARR)
	{
		if(memcmp(input1, input2, len) == 0)
		{
			printf(_GREEN "TEST%d VALID\n" _COLOR_RESET, testnum);
			if (!g_speedmode) usleep(0.075*1000000);
			return(0);
		}
		else
		{
			printf(_RED "TEST%d FAILED\n" _COLOR_RESET, testnum);
			if (!g_speedmode) usleep(0.075*1000000);
			return(1);
		}
	}
	if(mode == _VAL)
		return (simple_test((int)input1, (int)input2, testnum));
	return (-1);
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
int  simple_test(int input1, int input2, int testnum)
{
	if (input1 == input2)
		{
			printf(_GREEN "TEST%d VALID\n" _COLOR_RESET, testnum);
			if (!g_speedmode) usleep(0.075*1000000);
			return(0);
		}
		else
		{
			printf(_RED "TEST%d FAILED\n" _COLOR_RESET, testnum);
			if (!g_speedmode) usleep(0.075*1000000);
			return(1);
		}
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
int  zero_neg_pos_test(int input1, int input2, int testnum)
{
	if ((input1 == 0 && input2 == 0) || (input1 > 0 && input2 > 0)
			|| (input1 < 0 && input2 < 0))
		{
			printf(_GREEN "TEST%d VALID\n" _COLOR_RESET, testnum);
			if (!g_speedmode) usleep(0.075*1000000);
			return(0);
		}
		else
		{
			printf(_RED "TEST%d FAILED\n" _COLOR_RESET, testnum);
			if (!g_speedmode) usleep(0.075*1000000);
			return(1);
		}
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
void  ResetStringsNArrays(char *s1, char *s2, const char *orgs,\
							long *a1, long *a2, const long *orga, int mode)
{
	if(mode == _BOTH)
	{
		memcpy(a1, orga, 12 * sizeof(long));
		memcpy(a2, orga, 12 * sizeof(long));
		strcpy(s1, orgs);
		strcpy(s2, orgs);
	}
	if(mode == _ARR)
	{
		memcpy(a1, orga, 12 * sizeof(long));
		memcpy(a2, orga, 12 * sizeof(long));
	}
	if(mode == _STR)
	{
		strcpy(s1, orgs);
		strcpy(s2, orgs);
	}
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
void	ResetDoublePointer(void *p1, void *p2)
{
	free(p1);
	free(p2);
	p1 = NULL;
	p2 = NULL;
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
int   ResultCheck(int *TestResultCount, int *LastCount)
{
	if(*TestResultCount != *LastCount)
	{
		*LastCount = *TestResultCount;
		return(1);
	}
	return(0);
}

// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
char	*TestResultMsg(int result)
{
	if(result == 0)
		return("COMPLETED");
	else if (result == 1)
		return("FAILED");
	else
		return("ERROR in testprogram - please correct code.");
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
void	StartCountdown(int countdowntimer)
{
	printf("\n\nOK, THERE WE GO!... Are you ready??\n\n\n\n");
	while (countdowntimer > 9)
	{
		printf(_COLOR_RESET"\e[1m   «  _____ %d _____  »  \n\n\n\n", countdowntimer);
		countdowntimer--;
		fflush(stdout);
		if (!g_speedmode) usleep(1*1000000);
		printf("\e[4A");
	}
	while (countdowntimer > 3)
	{
		printf(_COLOR_RESET"\e[1m   «  _____ %d _____  »   \n\n\n\n", countdowntimer);
		countdowntimer--;
		fflush(stdout);
		if (!g_speedmode) usleep(1*1000000);
		printf("\e[4A");
	}
	while (countdowntimer > 2)
	{
		printf(_COLOR_RESET"\e[1;3%dm   «  _____ %d _____  »   \n\n\n\n", countdowntimer, countdowntimer);
		countdowntimer--;
		fflush(stdout);
		if (!g_speedmode) usleep(1*1000000);
		printf("\e[4A");
	}
	while (countdowntimer > 1)
	{
		printf(_COLOR_RESET"\e[1;3%dm   «        %d        »   \n\n\n\n", countdowntimer, countdowntimer);
		countdowntimer--;
		fflush(stdout);
		if (!g_speedmode) usleep(1*1000000);
		printf("\e[4A");
	}
	while (countdowntimer > 0)
	{
		printf(_COLOR_RESET"\e[1;3%dm            %d            \n\n\n\n", countdowntimer, countdowntimer);
		countdowntimer--;
		fflush(stdout);
		if (!g_speedmode) usleep(1*1000000);
		printf("\e[4A");
	}
	printf("\e[K\n\n\n\n");
	fflush(stdout);
	if (!g_speedmode) usleep(0.15*1000000);
	printf(_COLOR_RESET);
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
void	ProjectResultMsg(int ac, char *candidate, int result)
{
	if(result == 0)
		if(ac == 2)
			printf(_GREEN "\e[1m" "\n\n\n* * * * *  TESTS FULLY PASSED. Congrats %s!  * * * * *\n\n"\
					"\e[0;32m", candidate);
		else
			printf(_GREEN "\e[1m" "\n\n\n* * * * *  TESTS FULLY PASSED. Congrats!  * * * * *\n\n"\
					_GREEN);
	else
		if(ac == 2)
		{
			printf(_RED "\e[1m" "\n\n\nSorry %s, you failed %d tests."
							" Let's see where it went wrong!\n\n"
					_RED, candidate, result);
		}
		else
		{
			printf(_RED "\e[1m" "\n\n\nSorry, you failed %d tests."
							" Let's see where it went wrong!\n\n"
					_RED, result);
		}
}
