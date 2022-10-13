/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fras <fras@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/31 12:44:58 by fras          #+#    #+#                 */
/*   Updated: 2022/10/11 17:43:09 by fras          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <string.h>

#define _BOTH  3
#define _ARR   2
#define _STR   1

int		test_s(char *str1, char *str2, int testnum);
int		test_a(void *arr1, void *arr2, int n, int testnum);
int   ResultCheck(int *TRC, int *LC);
char	*TestResultMsg(int result);
void	ProjectResultMsg(int ac, char *candidate, int result);
void  ResetStringsNArrays(char *s1, char *s2, char *os,\
                          long *a1, long *a2, long *oa, int md);

int		main(int argc, char *argv[])
{
	char orgs[] = "Hello[zero this out] welcome to codam.";
	char str1[] = "Hello[zero this out] welcome to codam.";
	char str2[] = "Hello[zero this out] welcome to codam.";

  char rtn1[64];
	char rtn2[64];
  
  long orga[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
                  57, 123, -4875769, 111, 222, 333};
  long arr1[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
                  57, 123, -4875769, 111, 222, 333};
  long arr2[12] = {0, 4294967254, -2147483648, 6983975, 444, 7,\
                    57, 123, -4875769, 111, 222, 333};
  
  long rtn3[32] = {0};
  long rtn4[32] = {0};
  
  /*char empty_str1[] = "";
  char empty_str2[] = "";*/
	
  char candidate[32];

  int TestResultCount = 0;
  int LastCount = 0;
  int check = 0;
	int t = 0;
  int i = 3;

	if(argc == 2)
		strcpy(candidate, argv[1]);
	#define FCNAME "TEST PROGRAM"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
  printf("Testprogram: "); TestResultCount += test_s(str1, str2, t++);	
  /*printf("\n%s\n%s\n\n", str1, str2);*/					                //test start
  check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));
  
  if (check != 0)
    return(0);
  printf("\n\nOK, THERE WE GO!...");
  while (i > 0)
  {
    printf("{%d}", i--);
    fflush(stdout);
    sleep(1);
    printf("\b\b\b");
  }
  printf("   ");
  fflush(stdout);
  sleep(1);
  

  //memset.c
  #undef FCNAME
	#define FCNAME "ft_memset.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	strncpy(rtn1, memset(str1 + 5, '0', 15 * (sizeof(char))), sizeof(orgs));      //function call + save return
	strncpy(rtn2, ft_memset(str2 + 5, '0', 15 * (sizeof(char))), sizeof(orgs));   //function call	+ save return
  TestResultCount += test_s(rtn1, rtn2,  t++);                                  //test return value
	TestResultCount += test_s(str1, str2, t++);						                        //test after call
	/*printf("\n%s\n%s\n", str1, str2);
	printf("\n%s\n%s\n", rtn1, rtn2);*/
  memset(arr1, -1, sizeof(orga));
  ft_memset(arr2, -1, sizeof(orga));
  TestResultCount += test_a(arr1, arr2, sizeof(orga), t++);
  check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));

  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _BOTH);
  sleep(1);

	//bzero.c
	#undef FCNAME
	#define FCNAME "ft_bzero.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	bzero(str1 + 5, 15 * (sizeof(char)));
	ft_bzero(str2 + 5, 15 * (sizeof(char)));
	TestResultCount += test_s(str1, str2, t++);
	TestResultCount += test_s(str1 + 19, str2 + 19, t++);
	TestResultCount += test_s(str1 + 20, str2 + 20, t++);
	/*printf("After call:\n{\"%s\"}\n{\"%s\"}\n", str1, str2);
	printf("'(str + 19)':\n{\"%s\"}\n{\"%s\"}\n", str1 + 19, str2 + 19);
	printf("'(str + 20)':\n{\"%s\"}\n{\"%s\"}\n\n", str1 + 20, str2 + 20);*/
  check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));

  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _STR);
  sleep(1);

	//memcpy.c
	#undef FCNAME
	#define FCNAME "ft_memcpy.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);

  memcpy(rtn3, memcpy(arr1 + 9, orga, 3 * sizeof(long)), 3 * sizeof(long));
  memcpy(rtn4, ft_memcpy(arr2 + 9, orga, 3 * sizeof(long)), 3 * sizeof(long));
  TestResultCount += test_a(arr1, arr2, sizeof(orga), t++);
  TestResultCount += test_a(rtn3, rtn4, sizeof(rtn3), t++);
  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _ARR);

  memcpy(arr1 + 9, arr1, 3 * sizeof(long));
  ft_memcpy(arr2 + 9, arr2, 3 * sizeof(long));
  TestResultCount += test_a(arr1, arr2, sizeof(orga), t++);
  strncpy(rtn1, memcpy(str1 + 20, orgs + 5, 15), sizeof(orgs));
  strncpy(rtn2, ft_memcpy(str2 + 20, orgs + 5, 15), sizeof(orgs));
  TestResultCount += test_a(str1, str2, sizeof(orgs), t++);
  TestResultCount += test_a(rtn1, rtn2, sizeof(orgs), t++);

 /* for(int i = 0; i < 12; i++)
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
  printf("\n%s\n%s\n", str1, str2);*/
  check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));

  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _BOTH);
	sleep(1);
  
 /* #undef FCNAME
	#define FCNAME "ft_memccpy.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
  memccpy(arr1, arr1 + 1, 111, sizeof(orga) - 1);
  ft_memccpy(arr2, arr2 + 1, 111, sizeof(orga) - 1);
  TestResultCount += test_a(arr1, arr2, sizeof(orga), t++);
  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _ARR); // test end
  memccpy(arr1, arr1 + 1, -2147483648, sizeof(orga) - 1);
  ft_memccpy(arr2, arr2 + 1, -2147483648, sizeof(orga) - 1);
  TestResultCount += test_a(arr1, arr2, sizeof(orga), t++);
  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _ARR); // test end
  memccpy(arr1, arr1 + 1, 4444, sizeof(orga) - sizeof(long));
  ft_memccpy(arr2, arr2 + 1, 4444, sizeof(orga) - sizeof(long));
  TestResultCount += test_a(arr1, arr2, sizeof(orga), t++);
  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _ARR); // test end
  
  for(int i = 0; i < 12; i++)
    printf("%ld, ", arr1[i]);
  putchar('\n');
  check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));*/

	//--FINAL RESULTS--
	ProjectResultMsg(argc, candidate, TestResultCount);
	return(0);
}

int		test_s(char *str1, char *str2, int testnum)
{
  if(strcmp(str1, str2) == 0)
	{
	  printf("TEST%d VALID\n", testnum);
	    return(0);
	}
	else
	{
	  printf("TEST%d FAILED\n", testnum);
	  return(1);
  }
}

int		test_a(void *arr1, void *arr2, int n, int testnum)
{
  if(memcmp(arr1, arr2, n) == 0)
	{
	  printf("TEST%d VALID\n", testnum);
	    return(0);
	}
	else
	{
	  printf("TEST%d FAILED\n", testnum);
	  return(1);
  }
}

void  ResetStringsNArrays(char *s1, char *s2, char *os,\
                          long *a1, long *a2, long *oa, int md)
{
  if(md == _BOTH)
  {
    memcpy(a1, oa, sizeof(*oa));
    memcpy(a2, oa, sizeof(*oa));
    strncpy(s1, os, sizeof(*os));
	  strncpy(s2, os, sizeof(*os));
  }
  if(md == _ARR)
  {
    memcpy(a1, oa, sizeof(*oa));
    memcpy(a2, oa, sizeof(*oa));
  }
  if(md == _STR)
  {
    strncpy(s1, os, sizeof(*os));
	  strncpy(s2, os, sizeof(*os));
  }
}

int   ResultCheck(int *TRC, int *LC)
{
  if(*TRC != *LC)
  {
    *LC = *TRC;
    return(1);
  }
  return(0);
}

char	*TestResultMsg(int result)
{
	if(result == 0)
		return("COMPLETED");
	else
		return("FAILED");
	return(0);
}

void	ProjectResultMsg(int ac, char *candidate, int result)
{
	if(result == 0)
		if(ac == 2)
			printf("\n\n\n* * * * *  TESTS FULLY PASSED. Congrats %s!  * * * * *\n\n"
            , candidate);
		else
			printf("\n\n\n* * * * *  TESTS FULLY PASSED. Congrats!  * * * * *\n\n");
	else
		if(ac == 2)
		{
			printf("\n\n\nSorry %s, you failed %d tests."
			        " Let's see where it went wrong!\n\n"
              , candidate, result);
		}
		else
		{
			printf("\n\n\nSorry, you failed %d tests."
		          " Let's see where it went wrong!\n\n"
              , result);
		}
}
