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

void komut_calistir(char *args[], int giris_fd, int cikis_fd, int kapatilacak_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        if (giris_fd != -1) {
            dup2(giris_fd, STDIN_FILENO);
            close(giris_fd);
        }
        if (cikis_fd != -1) {
            dup2(cikis_fd, STDOUT_FILENO);
            close(cikis_fd);
        }
        if (kapatilacak_fd != -1) {
            close(kapatilacak_fd);
        }
        execvp(args[0], args);
        perror("execvp basarisiz");
        exit(1);
    } else if (pid > 0) {
        // parent
    } else {
        printf("fork basarisiz\n");
    }
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
          komut_calistir(args, -1, fd, -1);
          close(fd);
          wait(NULL);
        }
        else if(komut2 != NULL)
        {
          int fd[2];
          pipe (fd);
          komut_calistir(args, -1, fd[1], fd[0]);
          komut_calistir(args2, fd[0], -1, fd[1]);
          close(fd[0]);
          close(fd[1]);
          wait(NULL);
          wait(NULL);
        }
        else
        {
          komut_calistir(args, -1, -1, -1);
          wait(NULL);
        }
      }
    }
    return 0;
}
