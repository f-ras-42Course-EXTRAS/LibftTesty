/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   LibftTesty.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fras <fras@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/31 12:44:58 by fras          #+#    #+#                 */
/*   Updated: 2024/07/15 19:10:15 by fras          ########   odam.nl         */
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
#define _STRMALLOC		5

#define _GREEN			"\e[0;32m"
#define _RED			"\e[0;31m"
#define _COLOR_RESET	"\e[0m"


int		test(void *input1, void *input2, int len, int testnum, int mode);
int		simple_test(int input1, int input2, int testnum);
int  	zero_neg_pos_test(int input1, int input2, int testnum);
int		ResultCheck(int *TestResultCount, int *LastCount);
char	*TestResultMsg(int result);
void	ProjectResultMsg(int ac, char *candidate, int result);
void	ResetStringsNArrays(char *s1, char *s2, const char *orgs,\
							long *a1, long *a2, const long *orga, int mode);
void	ResetDoublePointer(void *p1, void *p2);
void	StartCountdown (int countdowntimer);
int		t_list_test(void *input1, t_list *input2, int testnum);

int	g_speedmode = 0;


static char testfunc(unsigned int i, char c)
{
	if (i < 20)
	{
		if (c >= 'a' && c <= 'z')
			return (c - 32);
		else if (c >= 'A' && c <= 'Z')
			return (c + 32);
		else
			return (c);
	}
	return (c);
}

static void testfunc2(unsigned int i, char *c)
{
	if (i < 20)
	{
		if (*c >= 'a' && *c <= 'z')
			*c = *c - 32;
		else if (*c >= 'A' && *c <= 'Z')
			*c = *c + 32;
	}
}

// static void testlstdel(void *content)
// {
// 	free(content);
// 	content = NULL;
// }

int		main(int argc, char *argv[])
{
	const char		orgs[] = "Hello[zero this out] welcome to Codam.";
	char			str1[] = "Hello[zero this out] welcome to Codam.";
	char			str2[] = "Hello[zero this out] welcome to Codam.";
	char 			orgsx[27 + 39] = "Let's concatenate!!!!!!!: ";
	char 			str3[27 + 39] = "Let's concatenate!!!!!!!: ";
	char 			str4[27 + 39] = "Let's concatenate!!!!!!!: ";
	char 			empty_str[] = "";
	char 			*malloc_str1 = malloc(64 * sizeof(*malloc_str1));
	char 			*malloc_str2 = malloc(64 * sizeof(*malloc_str2));
	
	const long		orga[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
						57, 123, -4875769, 111, 222, 333};
	long			arr1[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
						57, 123, -4875769, 111, 222, 333};
	long			arr2[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
						57, 123, -4875769, 111, 222, 333};
	unsigned char	arr3[256];
	signed char		arr4[256];
	int 			arr5[7] = {0, 6, 1, -1, 444, 7, 57};
	
	char			rtn1[64];
	char			rtn2[64];
	long			rtn3[32] = {0};
	long			rtn4[32] = {0};
	char			rtn5[256];
	char			rtn6[256];
	size_t			rtn7;
	size_t			rtn8;
	size_t			*ptr1;
	char			*ptr2;
	char			*ptr3;

	char 			candidate[32];
	int				testerror;
	int 			TestResultCount;
	int 			LastCount;
	int 			check;
	int 			t;
	int 			countdowntimer;

	testerror = 0;
	TestResultCount = 0;
	LastCount = 0;
	check = 0;
	t = 0;
	countdowntimer = 10;
	if (argc == 3 && strcmp(argv[2], "BONUSMODE") == 0)
	{
		#define bonus
		strcpy(candidate, argv[1]);
	}
	else if (argc == 2 && strcmp(argv[1], "BONUSMODE") == 0)
	{
		#define bonus
	}
	if (argc == 3 && strcmp(argv[2], "SPEEDMODE") == 0)
	{
		g_speedmode = 1;
		#define bonus
		strcpy(candidate, argv[1]);
	}
	else if (argc == 2 && strcmp(argv[1], "SPEEDMODE") == 0)
	{
		g_speedmode = 1;
		#define bonus
	}
	else if (argc == 2)
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
	TestResultCount += test(strnstr("Weeeelcome", "elc", 100),\
	 ft_strnstr("Weeeelcome", "elc", 100), 0, t++, _STR);
	printf("OR: %s\nFT: %s\n", strnstr("Weeeelcome", "elc", 100),\
	 ft_strnstr("Weeeelcome", "elc", 100));
	TestResultCount += test(strnstr("Weeelcome", "eelc", -1),\
	 ft_strnstr("Weeeelcome", "eelc", -1), 0, t++, _STR);
	printf("OR: %s\nFT: %s\n", strnstr("Weeelcome", "eelc", -1),\
	 ft_strnstr("Weeeelcome", "eelc", -1));
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
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_joinstr.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ptr2 = ft_strjoin("Hello", "Hello");
	TestResultCount += test("HelloHello", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n","HelloHello", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strjoin(str1, "");
	TestResultCount += test(str1, ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n",str1, ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strjoin("", str2);
	TestResultCount += test(str2, ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", str2, ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strjoin("", "");
	TestResultCount += test(empty_str, ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", empty_str, ptr2);
	free(ptr2);
	ptr2 = NULL;
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strtrim.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ptr2 = ft_strtrim("xxyyaaayxz  hello x ,,  zx  xx z", "z yax");
	TestResultCount += test("hello x ,,", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "hello x ,,", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strtrim("xxyyaaayxz  hello x ,,  zx  xx z", "");
	TestResultCount += test("xxyyaaayxz  hello x ,,  zx  xx z", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "xxyyaaayxz  hello x ,,  zx  xx z", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strtrim("", "");
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strtrim("1", "1");
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strtrim("1", "");
	TestResultCount += test("1", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "1", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strtrim("12", "12");
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strtrim("12", "12");
	TestResultCount += test("", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strtrim("xxyyaaayxz    zx  xx zhello x ,,", "z yax");
	TestResultCount += test("hello x ,,", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "hello x ,,", ptr2);
	free(ptr2);
	ptr2 = NULL;
	ptr2 = ft_strtrim("hello x ,,xxyyaaayxz    zx  xx z", "z yax");
	TestResultCount += test("hello x ,,", ptr2, 0, t++, _STR);
	printf("E: %s\nY: %s\n", "hello x ,,", ptr2);
	free(ptr2);
	ptr2 = NULL;
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_split.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	char **splitsing;
	int i;
	i = 0;
	splitsing = ft_split("Hallo1 Hallo2 Hallo3", ' ');
	TestResultCount += test("Hallo1", splitsing[0], 0, t++, _STR);
	TestResultCount += test("Hallo2", splitsing[1], 0, t++, _STR);
	TestResultCount += test("Hallo3", splitsing[2], 0, t++, _STR);
	TestResultCount += test(NULL, splitsing[3], 0, t++, _STR);
	while (splitsing[i])
	{
		printf("%s\n", splitsing[i]);
		free(splitsing[i++]);
	}
	free(splitsing);
	i = 0;
	splitsing = ft_split("Hello who is there?", ' ');
	TestResultCount += test("Hello", splitsing[0], 0, t++, _STR);
	TestResultCount += test("who", splitsing[1], 0, t++, _STR);
	TestResultCount += test("is", splitsing[2], 0, t++, _STR);
	TestResultCount += test("there?", splitsing[3], 0, t++, _STR);
	TestResultCount += test(NULL, splitsing[4], 0, t++, _STR);
	while (splitsing[i])
	{
		printf("%s\n", splitsing[i]);
		free(splitsing[i++]);
	}
	free(splitsing);
	i = 0;
	splitsing = ft_split("   It     is          me    ! !!  !!!    " , ' ');
	TestResultCount += test("It", splitsing[0], 0, t++, _STR);
	TestResultCount += test("is", splitsing[1], 0, t++, _STR);
	TestResultCount += test("me", splitsing[2], 0, t++, _STR);
	TestResultCount += test("!", splitsing[3], 0, t++, _STR);
	TestResultCount += test("!!", splitsing[4], 0, t++, _STR);
	TestResultCount += test("!!!", splitsing[5], 0, t++, _STR);
	TestResultCount += test(NULL, splitsing[6], 0, t++, _STR);
	while (splitsing[i])
	{	
		printf("%s\n", splitsing[i]);
		free(splitsing[i++]);
	}
	free(splitsing);
	i = 0;
	splitsing = ft_split("Oh,hello.", ' ');
	TestResultCount += test("Oh,hello.", splitsing[0], 0, t++, _STR);
	TestResultCount += test(NULL, splitsing[1], 0, t++, _STR);
	while (splitsing[i])
	{	
		printf("%s\n", splitsing[i]);
		free(splitsing[i++]);
	}
	free(splitsing);
	i = 0;
	splitsing = ft_split("", ' ');
	TestResultCount += test(NULL, splitsing[0], 0, t++, _STR);
	printf("%s\n", splitsing[0]);
	free(splitsing);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_itoa.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += test("-234", ft_itoa(-234), 0, t++, _STRMALLOC);
	TestResultCount += test("0", ft_itoa(0), 0, t++, _STRMALLOC);
	TestResultCount += test("0", ft_itoa(-0), 0, t++, _STRMALLOC);
	TestResultCount += test("1000000", ft_itoa(1000000), 0, t++, _STRMALLOC);
	TestResultCount += test("-1", ft_itoa(-1), 0, t++, _STRMALLOC);
	TestResultCount += test("-2147483648", ft_itoa(-2147483648), 0, t++, _STRMALLOC);
	TestResultCount += test("-2147483647", ft_itoa(-2147483647), 0, t++, _STRMALLOC);
	TestResultCount += test("2147483647", ft_itoa(2147483647), 0, t++, _STRMALLOC);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_strmapi.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	TestResultCount += test("hELLO[ZERO THIS OUT] welcome to Codam.",\
	 ft_strmapi(str1, &testfunc), 0, t++, _STRMALLOC);
	TestResultCount += test("",\
	 ft_strmapi(empty_str, &testfunc), 0, t++, _STRMALLOC);
	TestResultCount += test("h",\
	 ft_strmapi("H", &testfunc), 0, t++, _STRMALLOC);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_striteri.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ft_striteri(str1, &testfunc2);
	TestResultCount += test("hELLO[ZERO THIS OUT] welcome to Codam.",\
	 str1, 0, t++, _STR);
	ft_striteri(empty_str, &testfunc2);
	TestResultCount += test("", empty_str, 0, t++, _STR);
	ResetStringsNArrays(str3, str4, orgsx, arr1, arr2, orga, _STR);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_putchar_fd.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ft_putchar_fd('a', 0);
	ft_putchar_fd('\n', 0);
	ft_putchar_fd('a', 0);
	ft_putchar_fd('\n', 0);
	simple_test(1, 1, t++);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_putstr_fd.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ft_putstr_fd("hello", 1);
	ft_putstr_fd("\n", 1);
	simple_test(1, 1, t++);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_putendl_fd.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ft_putendl_fd("there!", 1);
	simple_test(1, 1, t++);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME


	if (!g_speedmode) usleep(0.15*1000000);

	#define FCNAME "ft_putnbr_fd.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	ft_putnbr_fd(1234, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(0, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-1234, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-1, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-2147483648, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(2147483647, 1);
	ft_putchar_fd('\n', 1);
	simple_test(1, 1, t++);
	check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	#undef FCNAME

	// // *************************************************************************************
	// //									B O N U S - PART
	// // *************************************************************************************
	
	// #ifdef bonus
	// t_list			*rtn9;
	// t_list			*rtn10;
	// t_list			*rtn11;
	
	// if (!g_speedmode) usleep(0.15*1000000);

	// #define FCNAME "ft_lstnew.c"
	// printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	// rtn9 = ft_lstnew("Hello");
	// printf("%s\n", rtn9->content);
	// printf("%p\n", rtn9->next),
	// TestResultCount += test("Hello", rtn9->content, 0, t++, _STR);
	// TestResultCount += test(NULL, rtn9->next, 0, t++, _STR);
	// free(rtn9);
	// check = ResultCheck(&TestResultCount, &LastCount);
	// printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	// #undef FCNAME
	
	// if (!g_speedmode) usleep(0.15*1000000);

	// #define FCNAME "ft_lstadd_front.c"
	// printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	// rtn9 = ft_lstnew("hello!");
	// printf("%s", rtn9->content);
	// rtn10 = ft_lstnew("There you are.. ");
	// printf("%s\n", rtn10->content);
	// printf("%p - %p\n", rtn9->next, rtn10->next);
	// ft_lstadd_front(&rtn9, rtn10);
	// printf("%s", rtn9->content);
	// printf("%s\n", rtn9->next->content),
	// TestResultCount += test("There you are.. ", rtn9->content, 0, t++, _STR);
	// TestResultCount += test("hello!", rtn9->next->content, 0, t++, _STR);
	// TestResultCount += test(NULL, rtn9->next->next, 0, t++, _STR);
	// free(rtn9->next);
	// free(rtn9);
	// check = ResultCheck(&TestResultCount, &LastCount);
	// printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	// #undef FCNAME

	// if (!g_speedmode) usleep(0.15*1000000);

	// #define FCNAME "ft_lstsize.c"
	// printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	// rtn9 = ft_lstnew("hello!");
	// rtn10 = ft_lstnew("There you are.. ");
	// ft_lstadd_front(&rtn9, rtn10);
    // simple_test(2, ft_lstsize(rtn9), t++);
	// free(rtn9->next);
	// free(rtn9);
	// rtn9 = ft_lstnew("hello!");
	// simple_test(1, ft_lstsize(rtn9), t++);
	// free(rtn9);
	// rtn9 = NULL;
	// simple_test(0, ft_lstsize(rtn9), t++);
	// check = ResultCheck(&TestResultCount, &LastCount);
	// printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	// #undef FCNAME

	// if (!g_speedmode) usleep(0.15*1000000);

	// #define FCNAME "ft_lstlast.c"
	// printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	// rtn9 = ft_lstnew("hello!");
	// rtn10 = ft_lstnew("There you are.. ");
	// ft_lstadd_front(&rtn9, rtn10);
	// rtn11 = ft_lstlast(rtn9);
    // test("hello!", rtn11->content, 0, t++, _STR);
	// test(NULL, rtn11->next, 0, t++, _STR);
	// free(rtn9->next);
	// free(rtn9);
	// rtn9 = ft_lstnew("hello!");
	// rtn11 = ft_lstlast(rtn9);
	// test("hello!", rtn11->content, 0, t++, _STR);
	// free(rtn9);
	// rtn9 = NULL;
	// check = ResultCheck(&TestResultCount, &LastCount);
	// printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	// #undef FCNAME

	// if (!g_speedmode) usleep(0.15*1000000);

	// #define FCNAME "ft_lstadd_back.c"
	// printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	// rtn9 = ft_lstnew("hello!");
	// rtn10 = ft_lstnew("There you are.. ");
	// ft_lstadd_back(&rtn9, rtn10);
	// TestResultCount += test("hello!", rtn9->content, 0, t++, _STR);
	// TestResultCount += test("There you are.. ", rtn9->next->content, 0, t++, _STR);
	// TestResultCount += test(NULL, rtn9->next->next, 0, t++, _STR);
	// free(rtn9->next);
	// free(rtn9);
	// rtn9 = NULL;
	// check = ResultCheck(&TestResultCount, &LastCount);
	// printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	// #undef FCNAME

	if (!g_speedmode) usleep(0.15*1000000);

	// #define FCNAME "ft_lstdelone.c"
	// printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	// malloc_str1 = "hello!";
	// rtn9 = ft_lstnew(malloc_str1);
	// TestResultCount += test(malloc_str1, rtn9->content, 0, t++, _STR);
	// // rtn9->next = rtn10;
	// // rtn10 = ft_lstnew("There you are.. ");
	// ft_lstdelone(rtn9, testlstdel);
	// // // TestResultCount += test("hello!", rtn9->content, 0, t++, _STR);
	// // TestResultCount += test("There you are.. ", rtn9->next->content, 0, t++, _STR);
	// // TestResultCount += test(NULL, rtn9->next->next, 0, t++, _STR);
	// // free(rtn9->next);
	// // free(rtn9);
	// check = ResultCheck(&TestResultCount, &LastCount);
	// printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	// #undef FCNAME


	// if (!g_speedmode) usleep(0.15*1000000);

	// #define FCNAME "TEST.c"
	// printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	// // Insert values
	// check = ResultCheck(&TestResultCount, &LastCount);
	// printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
	// #undef FCNAME
	// #endif

	//--FINAL RESULTS--
	ProjectResultMsg(argc, candidate, TestResultCount);
	return(0);
}
	


// -------------------------------------------------------------------------------------
//						HELPER FUNCTIONS BELOW
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
	if (mode == _STRMALLOC)
	{
		if(strcmp(input1, input2) == 0)
		{
			free(input2);
			printf(_GREEN "TEST%d VALID\n" _COLOR_RESET, testnum);
			if (!g_speedmode) usleep(0.075*1000000);
			return(0);
		}
		else
		{
			free(input2);
			printf(_RED "TEST%d FAILED\n" _COLOR_RESET, testnum);	
			if (!g_speedmode) usleep(0.075*1000000);
			return(1);
		}
	}
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
	while (countdowntimer > 5)
	{
		printf(_COLOR_RESET"\e[1m   «  _____ %d _____  »   \n\n\n\n", countdowntimer);
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
		printf("\e[K");
		printf("\e[1B");
	}
	while (countdowntimer > 2)
	{
		printf(_COLOR_RESET"\e[1;3%dm\n   «  _____ %d _____  »   \n\n\n\n", countdowntimer, countdowntimer);
		countdowntimer--;
		fflush(stdout);
		if (!g_speedmode) usleep(1*1000000);
		printf("\e[3A");
	}
	while (countdowntimer > 1)
	{
		printf(_COLOR_RESET"\e[1;3%dm\n   «        %d        »   \n\n\n\n", countdowntimer, countdowntimer);
		countdowntimer--;
		fflush(stdout);
		if (!g_speedmode) usleep(1*1000000);
		printf("\e[2A");
	}
	while (countdowntimer > 0)
	{
		printf(_COLOR_RESET"\e[1;3%dm\n            %d            \n\n\n\n", countdowntimer, countdowntimer);
		countdowntimer--;
		fflush(stdout);
		if (!g_speedmode) usleep(0.25*1000000);
		printf("\e[1A");
	}
	for (size_t i = 0; i < 50; i++)
	{
		printf("¨");
		fflush(stdout);
		if (!g_speedmode) usleep(0.01*1000000);
	}
	printf("LIFTOFF!\n\n\n\n");
	fflush(stdout);
	if (!g_speedmode) usleep(0.2*1000000);
	for (size_t i = 0; i < 11; i++)
	{
		printf("\e[4A");
		if (countdowntimer == 0)
			printf("\e[1;3%dm", countdowntimer += 1);
		else if (countdowntimer == 1)
			printf("\e[1;3%dm", countdowntimer += 2);
		else
			printf("\e[1;3%dm", countdowntimer -= 2);
		for (size_t i = 0; i < 50; i++)
			{
				printf("¨");
			}
		printf("LIFTOFF!\n\n\n\n");
		fflush(stdout);
		if (!g_speedmode) usleep(0.05*1000000);
	}
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
