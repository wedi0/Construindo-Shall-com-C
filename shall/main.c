#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define TAMANHO_MAX 60
#define PARSE_INPUT " "

//Execução do Shall .
int shellCmd(char **args) {
  pid_t pid, wpid;


  pid = fork();
  if(pid == 0) {
    

    if(execvp(args[0], args) == -1) {
      perror("Error");
    
    }
    exit(EXIT_FAILURE);
  }
  else if(pid < 0) {
    
    perror("Error");
  }

  return 1;
}


//Executar shall
int executarShall(char **args){
    //Aqui é onde  fazemos as escolhas com base no comando;
    if ( strcmp(args[0], "exit") == 0){
        return 0;
    }
    else if(strcmp(args[0], "cd") == 0){
        chdir(args[1]);
        return 1;
    }else if ( args[0] == 0){
        return 1;
    }

    return shellCmd(args);

}


//Transformando em tolkens
void parseToken(char **args, char **palavra){
    char *token;
    token = strtok(palavra, PARSE_INPUT); // Fazendo parse do primeiro comando do nosso arry args;
    args[0] = token; // setando nosso comando;

    //Parse para pegar os possiveis arguemntos digitados
    int i = 1;
    while ( i < sizeof(TAMANHO_MAX)){
                
        token = strtok(NULL, PARSE_INPUT);
        args[i] = token;
        i++;
    }

    args[i] = NULL;// setando o final do arry como NULL para podermos usarmos na função execvp
}

//Inserção 
void inserirComando(char *palavra){
   
    fgets(palavra, TAMANHO_MAX, stdin);//"Scan" que le os dados inseridos;

    int n = 0, aux = 1;
    //Primeiro parse para determinar o final das palavras inseridas;
    while (aux != 0)
    {
        if (palavra[n] == 10)
        {
            palavra[n] = 0; // Transforma o \n em 0 (flag usada para determinar o fim das palavras escritas)
            aux = 0; //  Seta 0 para encerrar o parse;
         }
        n++;
    }

    

}


//Executa o loop
void loopShall(){
    char palavra[TAMANHO_MAX], *args[TAMANHO_MAX]; //Variáveis que recebem todos os dados que vão ser inseridos;
    int e = 1; //Variável que controla o loop;

    do{

        printf("\n$: "); //Tela defult linux;
        inserirComando(palavra); //Captura dados;
        parseToken(args, palavra);//Transforma os dados em tolkens;

       
        e = executarShall(args);//Função que executa o shall;


    }while (e != 0);

}

int main(void){

    printf("\n ---WELCOME TO MY SHALL :D --- \n");
    loopShall();

    return 0;

}





