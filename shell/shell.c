#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
   char intput[100];
   char *args[10];
   while(1)
   {
      int i = 0;

      printf("$:");
      fgets(intput, sizeof(intput), stdin);
      intput[strcspn(intput, "\n")] = '\0';
      char *parca = strtok(intput, " ");
      while(parca != NULL)
      {
        args[i] = parca;
        i++;
        parca = strtok(NULL, " ");
      }
      args[i] = NULL;

      if(strcmp(args[0], "exit") == 0)
      {
        exit(0);
      }
      else if(strcmp(args[0], "cd")  == 0)
      {
        chdir(args[1]);
      }
      else
      {
        pid_t pid = fork();
        if(pid == 0)
        {

          // buradayım = ben child'ım
          execvp(args[0], args);
          perror("execvp basarisiz");
          exit(1);
        }
        else if  (pid > 0)
        {
          // buradayım = ben parent'ım
          wait(NULL);  // çocuğun bitmesini bekle
        }
        else
        {
          printf("fork basarisiz\n");
        }
      }
      printf("%s\n", intput);
    }
    return 0;
}
