/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testprog.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fras <fras@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/31 12:44:58 by fras          #+#    #+#                 */
/*   Updated: 2022/10/14 20:21:27 by fras          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <string.h>

#define _BOTH         3
#define _ARR          2
#define _STR          1

#define _GREEN        "\e[0;32m"
#define _RED          "\e[0;31m"
#define _COLOR_RESET  "\e[0m"


int		test(void *input1, void *input2, int len, int testnum, int mode);
int   ResultCheck(int *TestResultCount, int *LastCount);
char	*TestResultMsg(int result);
void	ProjectResultMsg(int ac, char *candidate, int result);
void  ResetStringsNArrays(char *s1, char *s2, char *orgs,\
                          long *a1, long *a2, long *orga, int mode);

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
	
  char candidate[32];

  int TestResultCount = 0;
  int LastCount = 0;
  int check = 0;
	int t = 0;
  int countdown = 3;

	if(argc == 2)
		strcpy(candidate, argv[1]);



	#define FCNAME "TEST PROGRAM"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
  printf("Testprogram: "); TestResultCount += test(str1, str2, _STR, t++, _STR);	
  printf("\n%s\n%s\n\n", str1, str2);                  					                //test start
  check = ResultCheck(&TestResultCount, &LastCount);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));

  if (check != 0)
    return(0);
  printf("\n\nOK, THERE WE GO!...");
  while (countdown > 0)
  {
    printf("{%d}", countdown--);
    fflush(stdout);
    sleep(1);
    printf("\b\b\b");
  }
  printf("   ");
  fflush(stdout);
  sleep(1);
  printf("\n\n");
  
  #undef FCNAME
	#define FCNAME "ft_memset.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	strncpy(rtn1, memset(str1 + 5, '0', 15 * (sizeof(char))), sizeof(orgs));      //function call + save return
	strncpy(rtn2, ft_memset(str2 + 5, '0', 15 * (sizeof(char))), sizeof(orgs));   //function call	+ save return
  TestResultCount += test(rtn1, rtn2, _STR, t++, _STR);                         //test return value
	TestResultCount += test(str1, str2, _STR, t++, _STR);						              //test after call
	printf("\n%s\n%s\n", str1, str2);
	printf("\n%s\n%s\n", rtn1, rtn2);
  memset(arr1, -1, sizeof(orga));
  ft_memset(arr2, -1, sizeof(orga));
  TestResultCount += test(arr1, arr2, sizeof(orga), t++, _ARR);
  check = ResultCheck(&TestResultCount, &LastCount);
  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _BOTH);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));

  sleep(1);

	#undef FCNAME
	#define FCNAME "ft_bzero.c"
	printf("\n\n%s\n-------------- %s --------------\n\n", FCNAME, FCNAME);
	bzero(str1 + 5, 15 * (sizeof(char)));
	ft_bzero(str2 + 5, 15 * (sizeof(char)));
	TestResultCount += test(str1, str2, _STR, t++, _STR);
	TestResultCount += test(str1 + 19, str2 + 19, _STR, t++, _STR);
	TestResultCount += test(str1 + 20, str2 + 20, _STR, t++, _STR);
	printf("\nAfter call:\n{\"%s\"}\n{\"%s\"}\n", str1, str2);
	printf("\n'(str + 19)':\n{\"%s\"}\n{\"%s\"}\n", str1 + 19, str2 + 19);
	printf("\n'(str + 20)':\n{\"%s\"}\n{\"%s\"}\n\n", str1 + 20, str2 + 20);
  check = ResultCheck(&TestResultCount, &LastCount);
  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _STR);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));

  sleep(1);

	#undef FCNAME
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

  check = ResultCheck(&TestResultCount, &LastCount);
  ResetStringsNArrays(str1, str2, orgs, arr1, arr2, orga, _BOTH);
	printf("\n----------------- %s -----------------\n\n", TestResultMsg(check));

	sleep(1);

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
    if(strcmp(input1, input2) == 0)
	  {
	    printf(_GREEN "TEST%d VALID\n" _COLOR_RESET, testnum);
      usleep(0.15*1000000);
	    return(0);
	  }
	  else
	  {
	    printf(_RED "TEST%d FAILED\n" _COLOR_RESET, testnum);	
      usleep(0.15*1000000);
	    return(1);
    }
  }
  if(mode == _ARR)
  {
    if(memcmp(input1, input2, len) == 0)
	  {
	    printf(_GREEN "TEST%d VALID\n" _COLOR_RESET, testnum);
      usleep(0.15*1000000);
      return(0);
	  }
	  else
  	{
	    printf(_RED "TEST%d FAILED\n" _COLOR_RESET, testnum);
	    usleep(0.15*1000000);
      return(1);
    }
  }
  return (-1);
}
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
void  ResetStringsNArrays(char *s1, char *s2, char *orgs,\
                          long *a1, long *a2, long *orga, int mode)
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
void	ProjectResultMsg(int ac, char *candidate, int result)
{
	if(result == 0)
		if(ac == 2)
			printf(_GREEN "\e[1m" "\n\n\n* * * * *  TESTS FULLY PASSED. Congrats %s!  * * * * *\n\n"
            , candidate);
		else
			printf(_GREEN "\e[1m" "\n\n\n* * * * *  TESTS FULLY PASSED. Congrats!  * * * * *\n\n");
	else
		if(ac == 2)
		{
			printf(_RED "\e[1m" "\n\n\nSorry %s, you failed %d tests."
			        " Let's see where it went wrong!\n\n"
              , candidate, result);
		}
		else
		{
			printf(_RED "\e[1m" "\n\n\nSorry, you failed %d tests."
		          " Let's see where it went wrong!\n\n"
              , result);
		}
}