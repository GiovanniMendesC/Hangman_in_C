#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
char palavra_secreta[30];
int erro;
char letraerrada[7]="";
char tema_secreto[30];

void menu(int *res);
void adiciona_palavra();
void peganome();
void escolhe_palavra();
void verificaletra();
void forca(int erro);
void tira_palavra();
void mostrahist();
void registravitoria(int vitoria);

int main(){
  int op, res=0;
  //garantindo que o arquivo dos jogadores existe
  FILE *fnome;
  fnome = fopen("jogadores.txt", "a+");
  if (fnome == NULL)
    printf("problemas ao abrir o arquivo jogadores! 1");
  fclose(fnome);
  //colcando para portuguÃªs
  setlocale(LC_ALL, "portuguese");
  //menu inicial
  do{
	  printf("\n\n\n\t\t\t\t\t\tBEM VINDO À FORCA :)\n\n\n\n\tPara começarmos, informe qual opção desjea:\n\n\t(1)COMEÇAR\t(2)ADICIONAR PALAVRA\t(3)EXCLUIR PALAVRA\t(4)HISTÓRICO\t(5)SAIR\n\n");
	  scanf("%d", &op);//fazer uma funçao para calcular o histórico ou apenas mostrar se acertou ou errou e outra para mostrar
	  system("cls");
	  //opção do menú
	  switch(op){
	    case 1://iniciando o jogo
	    peganome();
	    escolhe_palavra();
	    verificaletra();
	    menu(&res);
	    break;
	    case 2: //cadastrando palavras
	    adiciona_palavra();
	    menu(&res);
	    break;
	    case 3://removando palavra
	    tira_palavra();
	    menu(&res);
	    break;
		case 4://mostrando histórico
	    mostrahist();
	    menu(&res);
	    break;
	    case 5:
	    printf("\n\n\t\t\t\t\tObrigado por jogar :)\n\nDesenvolvido por: Giovanni Mendes Costa e Danylo Rodrigues Nunes\n\n");
	    getchar();
	    getchar();
	    return 0;
	    break;
	    default:
	    printf("\n opção inválida");
	  }
  }while(res==1);

  return 0;
}

void menu(int *res){//função para repetir o programa sem ter q abrir ele dnv
	printf("\nVoltar ao menu? (1-sim/0-nao)\n");
	fflush(stdin);
	scanf("%d", &*res);
	getchar();
	system("cls");
}

void adiciona_palavra(){
  FILE *filpalavra;
  FILE *ftema;
  int i, res, tema;
  char palavra[30], nome_tema[30];
  filpalavra = fopen("lista_palavras.txt", "a+");
  //verificando se abriu
  if (filpalavra==NULL)
    printf("\nFalha ao abrir o arquivo de palavras!");
	ftema=fopen("tema.txt", "a+");
	if (ftema==NULL){
		printf("problema ao abrir arquivo de temas");
	}
	printf("\nTEMAS\n1.ANIMAL\n2.COMIDA\n3.LUGAR\n4.PROFISSÂO\n5.PERSONAGEM\n6.OBJETO\n7.FRUTA\n8.COR\n9.VERBO\n10.PCH\n");
	printf("\nSua palavra pertence a qual tema?(informe o número)\n");
	fflush(stdin);
	scanf("%d", &tema);
	system("cls");
	switch(tema){
		case 1:
			strcpy(nome_tema, "ANIMAL");
		break;
		case 2:
			strcpy(nome_tema, "COMIDA");
		break;
		case 3:
			strcpy(nome_tema, "LUGAR");
			break;
		case 4:
			strcpy(nome_tema, "PROFISSÃO");
		break;
		case 5:
			strcpy(nome_tema, "PERSONAGEM");
		break;
		case 6:
			strcpy(nome_tema, "OBJETO");
		break;
		case 7:
			strcpy(nome_tema, "FRUTA");
		break;
		case 8:
			strcpy(nome_tema, "COR");
		break;
		case 9:
			strcpy(nome_tema, "VERBO");
		break;
		case 10:
			strcpy(nome_tema, "PCH");
		break;
		default:
			printf("opção inválida");
	}
	fflush(stdin);
  do{
    printf("Informe a palavra que deseja cadastrar: ");
    fgets(palavra, 30, stdin);
    for(i=0; palavra[i]!='\0'; i++){
      palavra[i]=toupper(palavra[i]);
    }
    printf("\ndigite 1 se a palavra desejada é ""%s"" e 0 caso contrário.\n", palavra);
    scanf("%d", &res);
  }while(res==0); //verificando a palavra
  //imprimindo no arquivo
  fprintf(filpalavra, "%s", palavra);
  fprintf(ftema, "%s\n", nome_tema);
  fclose(filpalavra);
  fclose(ftema);
}

void peganome(){
  char nome[30];
  FILE *fnome;
  int qt_nome=0, posicao=0, i, valido=1;
  fnome = fopen("jogadores.txt", "r");
  //verifica se abriu direito
  if (fnome == NULL)
    printf("Falha ao abrir o arquivo jogadores! 2");
  //olha quantos nomes tem escritos
  while(fgets(nome, 30, fnome)!=NULL){
    qt_nome++;
  }
  rewind(fnome);
  //copia os nomes numa matriz
  char nomes_arquivo[qt_nome][30];
  while(fgets(nome, 30, fnome)!=NULL){
    strcpy(nomes_arquivo[posicao], nome);//talvez tenha q abrir o arquivo dnv como "r+"
    posicao++;
  }
  fclose(fnome);
  //abrindo o arquivo para editar o texto
  fnome = fopen("jogadores.txt", "a+");
  if (fnome == NULL)
    printf("problema ao abrir arquivo dos jogadores!");
  //colocando o ponteiro no final do aqruivo para poder imrpimir o nome
  fseek(fnome, 0, SEEK_END);
  getchar();
  do{
    printf("informe seu nick: ");
    fgets(nome, 30, stdin);
    //verificando se não há outro nome igual
    for (i=0; i<qt_nome; i++){
      if (!strcmp(nome, nomes_arquivo[i])){
        printf("Esse nome ja existe!\n");
        valido=0;
      }
      else{
        valido = 1;
      }
    }
  }while(!valido);
  fprintf(fnome, "%s", nome);
  fclose(fnome);
  system("cls");
}


void escolhe_palavra(){
  FILE *fpalavra;
  FILE *ftema;
  char palavra[30], tema[30];
  int qt_palavra=0, posicao=0, posicao_tema=0;
  fpalavra = fopen("lista_palavras.txt", "r");
  //verificando se abriu
  if (fpalavra == 0)
    printf("Erro ao abrir arquivo!");
	ftema=fopen("tema.txt", "r");
	if (ftema==NULL)
	printf("erro ao abrir arquivo de temas");
  //contador de palavras
  rewind(fpalavra);
  while(fgets(palavra, 30, fpalavra)!=NULL){
    qt_palavra++;
  }
  rewind(fpalavra);
  //copia as palavras numa matriz string
  char arq_palavra[qt_palavra][30], arq_tema[qt_palavra][30];
  while(fgets(palavra, 30, fpalavra)!=NULL){
    strcpy(arq_palavra[posicao], palavra);
    posicao++;
  }
  //copia temas numa matriz string
  while(fgets(tema, 30, ftema)!=NULL){
  	strcpy(arq_tema[posicao_tema], tema);
  	posicao_tema++;
  }
  fclose(fpalavra);
  fclose(ftema);
  srand(time(NULL));
  //escolhe uma palavra aleatória para ser a secreta
  posicao = rand() % qt_palavra;
  posicao_tema = posicao;
  strcpy(palavra_secreta, arq_palavra[posicao]);
  strcpy(tema_secreto, arq_tema[posicao_tema]);
}


void verificaletra(){
  char letra;
  char palavra[30];
  int ganhou_perdeu = 0; //0 perdeu - 1 ganhou
  int i, vezes=0, erros=0, poleerra=0;
  strcpy(palavra, palavra_secreta);
  for (i=0; palavra[i+1]!='\0'; i++){
    if (vezes == 0){
      palavra[i]='_';
    }
  }
  //repete a pergunta da letra até elas serem iguais
  while(strcmp(palavra, palavra_secreta)){
    int  acertou=0;//acertou? 0=nÃ£o 1=sim
    forca(erros);
    for (i=0; palavra[i]!='\0'; i++){
        printf("%c ", palavra[i]);
    }
    printf("\ndiga uma letra: ");

    scanf("%c", &letra);
    getchar();
    system("cls");
    letra = toupper(letra);
    for (i=0; palavra[i]!='\0'; i++){
      if (letra == palavra_secreta[i]){
        palavra[i]=letra;
        vezes++;
        acertou = 1;
        //fazer uma função para acertar a forca e outra pra errar a forca
      }
    }
    vezes++;
    if (acertou==0){
    	letraerrada[poleerra]=letra;
    	poleerra++;
      erros++;
    }
    if (erros == 6){
      forca(erros);
      registravitoria(0);
      exit(0);
    }
  }
  registravitoria(1);
  printf("\nparabéns você acertou a palavra: %s", palavra);
  printf("\ntotal de erros: %d", erros);
}

void forca(int erro){
		//Desenho inicial da forca
		printf("tema: %serros: ", tema_secreto);
		if(erro == 0){
			printf("\n");
			printf("____________\n");
			printf("|          |\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("-\n\n");
		}
		else if(erro == 1){
			printf("%s\n", letraerrada);
			printf("____________\n");
			printf("|          |\n");
			printf("|          O\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("-\n\n");
		}
		else if(erro == 2){
			printf("%s\n", letraerrada);
			printf("____________\n");
			printf("|          |\n");
			printf("|          O\n");
			printf("|          |\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("-\n\n");
		}
		else if(erro == 3){
			printf("%s\n", letraerrada);
			printf("____________\n");
			printf("|          |\n");
			printf("|          O\n");
			printf("|         /|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("-\n\n");
		}
		else if(erro == 4){
			printf("%s\n", letraerrada);
			printf("____________\n");
			printf("|          |  \n");
			printf("|          O  \n");
			printf("|         /|\\  \n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("-\n\n");
		}
		else if(erro == 5){
			printf("%s\n", letraerrada);
			printf("____________\n");
			printf("|          |\n");
			printf("|          O \n");
			printf("|         /|\\  \n");
			printf("|           \\  \n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("-\n\n");
		}
		else if(erro == 6){
			printf("%s\n", letraerrada);
			printf("____________\n");
			printf("|          |\n");
			printf("|          O  \n");
			printf("|         /|\\  \n");
			printf("|         / \\  \n");
			printf("|\n");
			printf("|\n");
			printf("|\n");
			printf("-           Voce foi enforcado :( \n\n");
      printf("a palavra era: %s", palavra_secreta);
		}
}

void tira_palavra(){
  FILE *fpalavra;
  FILE *ftema;
  char palavra[30], tema[30], palavra_D[30];
  int qt_palavra=0, posicao=0, posicao_tema=0, i;
  fpalavra = fopen("lista_palavras.txt", "r");
  //verificando se abriu
  if (fpalavra == 0)
    printf("Erro ao abrir arquivo!");
    ftema=fopen("tema.txt", "r");
  //contador de palavras
  rewind(fpalavra);
  while(fgets(palavra, 30, fpalavra)!=NULL){
    qt_palavra++;
  }
  rewind(fpalavra);
  //copia as palavras numa matriz string
  char arq_palavra[qt_palavra][30], arq_tema[qt_palavra][30];
  while(fgets(palavra, 30, fpalavra)!=NULL){
    strcpy(arq_palavra[posicao], palavra);
    posicao++;
  }
  //copia temas numa matriz string
  while(fgets(tema, 30, ftema)!=NULL){
  	strcpy(arq_tema[posicao_tema], tema);
  	posicao_tema++;
  }

  for (i=0; i<qt_palavra; i++){
    printf("\n%d. %s\n", i+1, arq_palavra[i]);//mostra as palavras cadastradas
  }

  fclose(fpalavra);
  fclose(ftema);

  printf("\nqual palavra gostaria de retirar? (escreva a palavra) \n");
  getchar();
  fgets(palavra_D, 30, stdin);
  for (i=0; palavra_D[i]!='\0'; i++){
    palavra_D[i]=toupper(palavra_D[i]);//deixa a palavra em caixa alta pra n dar conflito
  }
  for (i=0; i<qt_palavra; i++){
    if (!strcmp(palavra_D, arq_palavra[i])){//verifica qual palavra do arquivo é igual
      strcpy(arq_palavra[i], "");
      strcpy(arq_tema[i], "");
    }
  }
  remove("lista_palavras.txt");//exclui o arquivo para n somar ao conteúdo anterior
  remove("tema.txt");
  fpalavra = fopen("lista_palavras.txt", "a+");
  if (fpalavra==NULL){
  	printf("erro ao abrir arquivo lista 3");
  }
  ftema = fopen("tema.txt", "a+");
  if (ftema ==NULL){
  	printf("erro ao abrir arquivo temas 3");
  }
  //escrevendo a matriz no arquivo
  for (i=0; i<qt_palavra; i++){
    fprintf(fpalavra, "%s", arq_palavra[i]);
    fprintf(ftema, "%s", arq_tema[i]);
  }
  printf("\npalavra excluída com sucesso!");
  fclose(fpalavra);
  fclose(ftema);
  system("cls");
}

void mostrahist(){
	printf("\n\n\n\t\t\t\t\t*********HISTÓRICO DE JOGOS*********\n\n\n");
	char nomes[30];
	int i=1;
	//abrindo arquivo para leitura
	FILE *fjogadores;
	fjogadores = fopen("jogadores.txt", "r");
	//verificando se abriu
	if(fjogadores == NULL){
		printf("Erro ao abrir arquivo de jogadores 3");
	}
	//pegando os nomes do arquivo que ja estarão alterados pela outra função
	while(fgets(nomes, 30, fjogadores)!=NULL){
		printf("%d. %s\n", i, nomes);
		i++;
	}
	fclose(fjogadores);
}

void registravitoria(int vitoria){//ganhou 1 - perdeu 0
	char nomes[30];
	int qt_nomes=0, posicao=0, i;
	FILE *fjogadores;
	fjogadores = fopen("jogadores.txt", "r");
	if (fjogadores==NULL){
		printf("problema ao abrir o arquivo jogadores 4");
	}
	while (fgets(nomes, 30, fjogadores)!=NULL){
		qt_nomes++;
	}
	rewind(fjogadores);
	char arq_nomes[qt_nomes][30];
	//copiando os nomes numa matriz string
	while (fgets(nomes, 30, fjogadores)!=NULL){
		strcpy(arq_nomes[posicao], nomes);
		posicao++;
	}
	fclose(fjogadores);
	//fazer uma variável para perdeu ou ganhou para escrever "PERDEU" e "GANHOU" no ultimo nome - que seria na "posicao" final
	if (vitoria == 1){
		strtok(arq_nomes[posicao-1], "\n");
		strcat(arq_nomes[posicao-1], " GANHOU\n");
	}
	if (vitoria == 0){
		strtok(arq_nomes[posicao-1], "\n");
		strcat(arq_nomes[posicao-1], " PERDEU\n");
	}
	remove("jogadores.txt");
	fjogadores=fopen("jogadores.txt", "a+");
	if (fjogadores==NULL){
		printf("problemas ao abrir arquivo de jogadores 5");
	}
	for (i=0; i<qt_nomes; i++){
		fprintf(fjogadores, "%s", arq_nomes[i]);
	}
	fclose(fjogadores);
}
