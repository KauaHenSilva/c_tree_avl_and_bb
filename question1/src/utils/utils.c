#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <ctype.h>


int debug_index = 0;
char *getDebugInput()
{
  char *buffer = malloc(12 * sizeof(char));
  if (buffer != NULL)
    snprintf(buffer, 12, "%d\n", debug_index++);
  return buffer;
}

int getString(char **string, const char *msg)
{
  char buffer[1024];
  while (1)
  {
    printf("%s", msg);
#if DEBUG_MODE
    char *debug_input = getDebugInput();
    if (debug_input != NULL)
    {
      strcpy(buffer, debug_input);
      printf("%s", buffer);
    }
    else
      return 0;
    free(debug_input);
#else
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
#endif
    {
      buffer[strcspn(buffer, "\n")] = '\0';
      if (strcmp(buffer, "sair") == 0)
        return 0;

      *string = malloc(strlen(buffer) + 1);
      if (*string != NULL)
      {
        strcpy(*string, buffer);
        return 1;
      }

      printf("Valor invalido!\n\n");
    }
  }
}

int getInt(int *inteiro, const char *msg)
{
  char buffer[1024];
  while (1)
  {
    printf("%s", msg);
#if DEBUG_MODE
    char *debug_input = getDebugInput();
    if (debug_input != NULL)
    {
      strcpy(buffer, debug_input);
      printf("%s", buffer); // Simulate user input
    }
    else
      return 0;
    free(debug_input);
#else
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
#endif
    {
      buffer[strcspn(buffer, "\n")] = '\0';
      if (strcmp(buffer, "sair") == 0)
        return 0;

      int is_number = 1;
      for (int i = 0; buffer[i] != '\0'; i++)
        if (!isdigit(buffer[i]))
        {
          is_number = 0;
          break;
        }

      if (is_number)
      {
        *inteiro = atoi(buffer);
        return 1;
      }
    }

    printf("Valor invalido!\n\n");
  }
}

int getIntInValues(int *values, int tamValue, int *number, const char *msg)
{
  char buffer[1024];
  while (1)
  {
    printf("%s", msg);
#if DEBUG_MODE
    int debug_input = values[rand() % tamValue];
    snprintf(buffer, sizeof(buffer), "%d\n", debug_input);
    printf("%s", buffer); // Simulate user input
#else
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
#endif
    {
      buffer[strcspn(buffer, "\n")] = '\0';
      if (strcmp(buffer, "sair") == 0)
        return 0;

      int is_number = 1;
      for (int i = 0; buffer[i] != '\0'; i++)
        if (!isdigit(buffer[i]))
        {
          is_number = 0;
          break;
        }

      if (is_number)
      {
        int input_value = atoi(buffer);
        for (int i = 0; i < tamValue; i++)
          if (input_value == values[i])
          {
            *number = input_value;
            return 1;
          }
      }
    }

    printf("Valor invalido!\n\n");
  }
}