#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

void parse_command(char *command, char *args[])
{
   int i = 0;
   char *parca = strtok(command, " ");
   while (parca != NULL) {
        args[i] = parca;
        i++;
        parca = strtok(NULL, " ");
   }
   args[i] = NULL;
}

int main()
{
   char intput[100];
   char *args[10];
   char *args2[10];
   char *dosya_adi = NULL;
   while(1)
   {

      printf("$:");
      fgets(intput, sizeof(intput), stdin);
      intput[strcspn(intput, "\n")] = '\0';
      char *yonlendirme =strchr(intput, '>');
      if (yonlendirme != NULL)
       {
         *yonlendirme = '\0';
         dosya_adi = yonlendirme +1;
         while(*dosya_adi == ' ')
         {
           dosya_adi++;
         }
       }
      char *komut1 = strtok(intput, "|");
      char *komut2 = strtok(NULL, "|");
      parse_command(komut1, args);
      if (komut2 != NULL) {
        parse_command(komut2, args2);
       }

      if (komut2 != NULL) printf("args2[0]=%s\n", args2[0]);
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
        if (yonlendirme != NULL)
        {
          int fd = open(dosya_adi, O_CREAT | O_WRONLY | O_TRUNC, 0644);
          pid_t pid = fork();
          if(pid == 0)
          {
            // ben child'ım, çıktım dosyaya gitsin
            dup2(fd, STDOUT_FILENO);
            close(fd);
            execvp(args[0], args);
            perror("execvp basarisiz");
            exit(1);
          }
          else if (pid > 0)
          {
           // parent
           close(fd);
           wait(NULL);
          }
          else
          {
            printf("fork basarisiz\n");
          }
        }
        else if(komut2 != NULL)
        {
          int fd[2];
          pipe(fd);
          pid_t pid1 = fork();
          if (pid1 == 0)
          {
            // ben ls child'ıyım
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp(args[0], args);
            perror("execvp basarisiz");
            exit(1);
 	  }
          pid_t pid2 = fork();
          if (pid2 == 0)
          {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp(args2[0], args2);
            perror("execvp basarisiz");
            exit(1);
          }
          close(fd[0]);
          close(fd[1]);
          wait(NULL);
          wait(NULL);
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
      }
    }
    return 0;
}
