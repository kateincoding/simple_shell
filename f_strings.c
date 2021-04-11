#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: array
 * Return: length
 */
int _strlen(const char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

/**
 * _strdup - copy a strings with a malloc
 * @s1: array
 * Return: pointer to the copy
 */
char *_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = (char *)malloc(sizeof(char) * _strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/**
 * _strcmp - compare if is equal 2 strings
 * @s1: string1
 * @s2: string2
 * Return: 0 success; else pointer 
 */
int	_strcmp(const char *s1, const char *s2)
{
	return (_strncmp(s1, s2, (size_t)-1));
}

/**
 * _strncmp - compare if is equal 2 strings, first n chars
 * @s1: string1
 * @s2: string2
 * Return: 0 success; else pointer 
 */
int	_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && s1 && s2 && s1[i] && s2[i] &&
			(unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}