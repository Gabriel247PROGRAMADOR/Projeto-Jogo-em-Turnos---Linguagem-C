#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define GREEK_CHARSET 16


// MS-DOS COLORS
void textcolor (int color)
{
    // BLACK=0, BLUE=1; GREEN=2; CYAN=3; RED=4; MAGENTA=5; BROWN=6; LIGHTGRAY=7; DARKGRAY=8;
    // LIGHTBLUE=9; LIGHTGREEN=10; LIGHTCYAN=11, LIGHTRED=12; LIGHTMAGENTA=13; YELLOW=14; WHITE=15
    static int __BACKGROUND;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}

void textoSequencial(const char *str, unsigned int delay)
{
    while (*str)
    {
        putchar(*str++);
        fflush(stdout);
        usleep(delay);
    }
}

int GeradorRandomico(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int main()
{

    setlocale(LC_ALL, "Portuguese");

    int min, max; //valores minimo e maximo
    int escolha; //armazena a escolha de ataque do jogador
    int escolhaclasse; //armazena qual classe o player escolheu
    int escolhaBoss; //ataque que o boss vai escolher
    int ale; //numero aleatorio de 1 a 100
    int dano; //dano que o player ou boss levar
    int cura; //cura que o player ou boss levar
    int vidaP = 1000; //vida do jogador
    int vidaB = 1750; //vida do boss

    //contadores
    int playerFalha = 0;
    int playerSucesso = 0;
    int playerCritico = 0;
    int bossFalha = 0;
    int bossSucesso = 0;
    int bossCritico = 0;


    int defesa = 0; // habilidade da classe cavaleiro
    int cont = 0; // contador
    int veneno = 0; // habilidade da classe assassino

    //funções mais importantes \/

    int porcentagem()
    {
        min = 1;
        max = 100;

        ale = GeradorRandomico(min, max);
    }

    int MostrarQuantVida()
    {

        textcolor(10);
        textoSequencial("SUA VIDA: ", 60000);
        printf("%d ", vidaP);
        textoSequencial("------- ", 20000);
        textoSequencial("VIDA BOSS: ", 60000);
        printf("%d \n\n", vidaB);

        //Funcao responsavel por imprimir a quantidade de vida do player e do boss. alem disso ela tambem verifica se o jogdor ou o boss foram mortos por algum ataque
    }

    int danoAoPlayer()
    {
        porcentagem();

        if(veneno == 1)
        {
            textcolor(2);
            textoSequencial("Veneno!!!\n", 75000);
            printf("%d ", dano);
            textoSequencial("- 5%...\n", 80000);
            dano = dano * 0.95;
        }else if(veneno == 2)
        {
            textcolor(2);
            textoSequencial("Veneno!!!\n", 75000);
            printf("%d ", dano);
            textoSequencial("- 10%...\n", 80000);
            dano = dano * 0.90;
        }else if(veneno == 3)
        {
            textcolor(2);
            textoSequencial("Veneno!!!\n", 75000);
            printf("%d ", dano);
            textoSequencial("- 15%...\n", 80000);
            dano = dano * 0.85;
        }

        //verificando se o player está com a defesa ativa e se conseguio se defender
        if(defesa == 0 || ale <= 50)
        {

            if(defesa == 1)
            {
                textcolor(12);
                textoSequencial("FALHA NO BLOQUEIO!\n\n", 70000);
            }

            porcentagem();

            if(ale <= 10)
            {
                textcolor(14);
                textoSequencial("DANO CRITÍCO!!!\n", 75000);
                printf("%d ", dano);
                textoSequencial("x 2...\n", 80000);
                dano = dano * 2;

                bossCritico += 1;
            }

            textcolor(4);
            textoSequencial("Boss causou ", 50000);
            printf("%d ", dano);
            textoSequencial("de dano a você\n", 50000);

            vidaP -= dano;

            MostrarQuantVida();
        }
        else
        {
            cura = 0;
            textcolor(6);
            textoSequencial("BLOQUEIO!\n\n", 75000);
        }
        //Função responsavel por caucular e imprimir o dano causado ao jogador pelo boss
    }

    int danoAoBoss()
    {
        porcentagem();

        if(ale <= 10)
        {
            textcolor(14);
            textoSequencial("DANO CRÍTICO!!!\n", 75000);
            printf("%d ", dano);
            textoSequencial("x 2...\n", 80000);
            dano = dano * 2;

            playerCritico += 1;
        }

        textcolor(4);
        textoSequencial("Você causou ", 50000);
        printf("%d ", dano);
        textoSequencial("de dano ao boss \n", 50000);

        vidaB -= dano;

        MostrarQuantVida();

        if(defesa == 1)
        {
            textcolor(6);
            textoSequencial("Redobrando guarda!\n\n", 60000);
        }

        //Função responsavel por caucular e imprimir o dano causado ao boss pelo jogador
    }

    int curaAoPlayer()
    {

        textcolor(9);
        textoSequencial("Você recuperou ", 50000);
        printf("%d ", cura);
        textoSequencial("de vida \n", 50000);

        vidaP += cura;

        if(vidaP > 1100 && escolhaclasse == 1)
        {
            vidaP = 1100;
            textoSequencial("Vida máxima obtida!\n", 50000);
        }
        else if(vidaP > 750 && escolhaclasse == 2)
        {
            vidaP = 750;
            textoSequencial("Vida máxima obtida!\n", 50000);
        }
        else if(vidaP > 975 && escolhaclasse == 3)
        {
            vidaP = 975;
            textoSequencial("Vida máxima obtida!\n", 50000);
        }

        MostrarQuantVida();

        //funcao responsavel por calcular e imprimir a cura obtida pelo jogador
    }

    int curaAoBoss()
    {
        if(cura > 0)
        {
            if(veneno == 1)
            {
                textcolor(2);
                textoSequencial("Veneno!!!\n", 75000);
                printf("%d ", cura);
                textoSequencial("- 20%...\n", 80000);
                cura = cura * 0.80;
            }else if(veneno == 2)
            {
                textcolor(2);
                textoSequencial("Veneno!!!\n", 75000);
                printf("%d ", cura);
                textoSequencial("- 25%...\n", 80000);
                cura = cura * 0.75;
            }else if(veneno == 3)
            {
                textcolor(2);
                textoSequencial("Veneno!!!\n", 75000);
                printf("%d ", cura);
                textoSequencial("- 30%...\n", 80000);
                cura = cura * 0.70;
            }

            textcolor(9);
            textoSequencial("Boss recuperou ", 60000);
            printf("%d ", cura);
            textoSequencial("de vida \n", 60000);

            vidaB += cura;

            if(vidaB > 1750)
            {
                vidaB = 1750;
                textoSequencial("Vida maxima obtida!\n", 50000);
            }

            MostrarQuantVida();
        }
        //funcao responsavel por calcular e imprimir a cura obtida pelo boss
    }

    int PlayerCuraPassiva()
    {
        if(vidaP < 1100 && escolhaclasse == 1)
        {
            min = 1;
            max = 5;

            textcolor(14);
            textoSequencial("\nCura passiva:\n", 50000);

            cura = GeradorRandomico(min, max);
            curaAoPlayer();

        }
        else if(vidaP < 750 && escolhaclasse == 2)
        {
            min = 5;
            max = 10;

            textcolor(14);
            textoSequencial("\nCura passiva:\n", 50000);

            cura = GeradorRandomico(min, max);
            curaAoPlayer();
        }
        else if(vidaP < 975 && escolhaclasse == 3)
        {
            min = 1;
            max = 5;

            textcolor(14);
            textoSequencial("\nCura passiva:\n", 50000);

            cura = GeradorRandomico(min, max);
            curaAoPlayer();
        }
    }


    int PlayerVeneno()
    {

        if(veneno == 1)
        {
            porcentagem();
            if(ale <= 70 && escolhaclasse == 3)
            {
                min = 5;
                max = 30;

                textcolor(2);
                textoSequencial("\nVeneno", 50000);
                printf(" %d :\n", veneno);

                dano = GeradorRandomico(min, max);
                danoAoBoss();
            }
            else
            {
                min = 5;
                max = 30;

                textcolor(2);
                textoSequencial("\nVeneno", 50000);
                printf(" %d :\n", veneno);

                dano = GeradorRandomico(min, max);
                danoAoBoss();

                textcolor(12);
                textoSequencial("(- 1) Veneno Anulado\n\n", 50000);
                veneno -= 1;
            }
        }else if(veneno == 2)
        {
            porcentagem();
            if(ale <= 70 && escolhaclasse == 3)
            {
                min = 10;
                max = 35;

                textcolor(2);
                textoSequencial("\nVeneno", 50000);
                printf(" %d :\n", veneno);

                dano = GeradorRandomico(min, max);
                danoAoBoss();
            }
            else
            {
                min = 10;
                max = 35;

                textcolor(2);
                textoSequencial("\nVeneno", 50000);
                printf(" %d :\n", veneno);

                dano = GeradorRandomico(min, max);
                danoAoBoss();

                textcolor(12);
                textoSequencial("(- 1) Veneno Anulado\n\n", 50000);
                veneno -= 1;
            }
        }else if(veneno == 3)
        {
            porcentagem();
            if(ale <= 70 && escolhaclasse == 3)
            {
                min = 15;
                max = 40;

                textcolor(2);
                textoSequencial("\nVeneno", 50000);
                printf(" %d :\n", veneno);

                dano = GeradorRandomico(min, max);
                danoAoBoss();
            }
            else
            {
                min = 15;
                max = 40;

                textcolor(2);
                textoSequencial("\nVeneno", 50000);
                printf(" %d :\n", veneno);

                dano = GeradorRandomico(min, max);
                danoAoBoss();

                textcolor(12);
                textoSequencial("(- 1) Veneno Anulado\n\n", 50000);
                veneno -= 1;
            }
        }
    }



    //classe assassino: tabela, habilidades e chances \/

    int TabelaDeHabilidadesClasse_Assassino()
    {
        textcolor(15);

        textoSequencial("Uso: | Quantidade (min e max): | Nome da habilidade: | Chance de sucesso:\n", 990);
        textoSequencial("-> 1 | (40 - 80)      dano     | Corte razo          | (90% de chance)   \n", 990);
        textoSequencial("-> 2 | (30 - 100)     dano     | Arremesso de adaga  | (72% de chance)   \n", 990);
        textoSequencial("-> 3 | (45 - 55)      dano     | Corte Triplo (x3)   | (60% de chance)   \n", 990);
        textoSequencial("-> 4 | (25 - 75) dano & cura   | Drenagem de vida    | (54% de chance)   \n", 990);
        textoSequencial("-> 5 | (50) dano & veneno(70%) | Corte envenenado    | (45% de chance)   \n\n", 990);
    }

    int PlayerDano_corteRazo()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 40;
        max = 80;

        //CHANCE DE ACERTAR
        if(ale <= 90)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoBoss();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_arremessoDeAdaga()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 30;
        max = 100;

        //CHANCE DE ACERTAR
        if(ale <= 72)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoBoss();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_corteTripo()
    {
        while(cont < 3)
        {

            cont++;
            porcentagem();

            //DANO || CURA, minimo e maximo
            min = 45;
            max = 55;

            //CHANCE DE ACERTAR
            if(ale <= 60)
            {

                textcolor(11);
                textoSequencial("\nSUCESSO!\n", 75000);
                playerSucesso += 1;

                dano = GeradorRandomico(min, max);
                danoAoBoss();
            }
            else
            {
                textcolor(12);
                textoSequencial("\nFALHA!\n\n", 75000);
                playerFalha += 1;
            }

        }
    }

    int PlayerCura_drenagemDeVida()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 25;
        max = 75;

        //CHANCE DE ACERTAR
        if(ale <= 54)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = GeradorRandomico(min, max);
            cura = dano;

            danoAoBoss();
            curaAoPlayer();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_corteEnvenenado()
    {
        porcentagem();

        //CHANCE DE ACERTAR
        if(ale <= 45)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            veneno += 1;

            if(veneno > 3){
                veneno = 3;
                textoSequencial("veneno máximo já atingido!\n", 75000);
            }

            dano = 50;
            danoAoBoss();

            textcolor(2);
            textoSequencial("(+ 1) Boss está envenenado!\n\n", 50000);
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int ChancesClasse_Assassino()
    {
        if(escolha == 1)
        {
            PlayerDano_corteRazo();
        }
        else if(escolha == 2)
        {
            PlayerDano_arremessoDeAdaga();
        }
        else if(escolha == 3)
        {
            PlayerDano_corteTripo();
        }
        else if(escolha == 4)
        {
            PlayerCura_drenagemDeVida();
        }
        else if(escolha == 5)
        {
            PlayerDano_corteEnvenenado();
        }
        else
        {
            textoSequencial("Essa opção nao existe, tente novamente: ", 50000);
            scanf("%d", &escolha);
            ChancesClasse_Assassino();
        }
    }

    //classe cavaleiro: tabela, habilidades e chances \/

    int TabelaDeHabilidadesClasse_Cavaleiro()
    {
        textcolor(15);

        textoSequencial("Uso: | Quantidade (min e max): | Nome da habilidade: | Chance de sucesso:\n", 990);
        textoSequencial("-> 1 | (40 - 70)      dano     | Escudada            | (93% de chance)   \n", 990);
        textoSequencial("-> 2 | (50 - 100)     cura     | Bandagem            | (80% de chance)   \n", 990);
        textoSequencial("-> 3 | (75 - 100)     dano     | Corte               | (74% de chance)   \n", 990);
        textoSequencial("-> 4 | (100 - 200)    dano     | Enfincada           | (57% de chance)   \n", 990);
        textoSequencial("-> 5 | (125) dano & defesa(50%)| Ataque e Defesa     | (42% de chance)   \n\n", 990);
    }

    int PlayerDano_escudada()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 40;
        max = 70;

        //CHANCE DE ACERTAR
        if(ale <= 93)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoBoss();

        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerCura_bandagem()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 50;
        max = 100;

        //CHANCE DE ACERTAR
        if(ale <= 80)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            cura = GeradorRandomico(min, max);
            curaAoPlayer();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_corte()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 75;
        max = 100;

        //CHANCE DE ACERTAR
        if(ale <= 74)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoBoss();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_enfincada()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 100;
        max = 200;

        //CHANCE DE ACERTAR
        if(ale <= 57)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoBoss();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_ataqueEdefesa()
    {
        porcentagem();

        //CHANCE DE ACERTAR
        if(ale <= 42)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            defesa = 1;

            dano = 125;
            danoAoBoss();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int ChancesClasse_Cavaleiro()
    {
        if(escolha == 1)
        {
            PlayerDano_escudada();
        }
        else if(escolha == 2)
        {
            PlayerCura_bandagem();
        }
        else if(escolha == 3)
        {
            PlayerDano_corte();
        }
        else if(escolha == 4)
        {
            PlayerDano_enfincada();
        }
        else if(escolha == 5)
        {
            PlayerDano_ataqueEdefesa();
        }
        else
        {
            textoSequencial("Essa opção nao existe, tente novamente: ", 50000);
            scanf("%d", &escolha);
            ChancesClasse_Cavaleiro();
        }
    }

    //classe pistoleiro: tabela, habilidades e chances \/

    int TabelaDeHabilidadesClasse_Pistoleiro()
    {
        textcolor(15);

        textoSequencial("Uso: | Quantidade (min e max): | Nome da habilidade: | Chance de sucesso:\n", 990);
        textoSequencial("-> 1 | (55)           dano     | Tiro Preciso        | (98% de chance)   \n", 990);
        textoSequencial("-> 2 | (80 - 115)     dano     | Arremesso de faca   | (68% de chance)   \n", 990);
        textoSequencial("-> 3 | (125 - 175)    dano     | Tiro na cabeca      | (53% de chance)   \n", 990);
        textoSequencial("-> 4 | (90 - 100)     cura     | Café Preto          | (51% de chance)   \n", 990);
        textoSequencial("-> 5 | (30 - 70)      dano     | 6 tiros (x6)        | (45% de chance)   \n\n", 990);
    }

    int PlayerDano_tiroPreciso()
    {
        porcentagem();

        //CHANCE DE ACERTAR
        if(ale <= 98)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = 55;
            danoAoBoss();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_arremessoDeFaca()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 80;
        max = 115;

        //CHANCE DE ACERTAR
        if(ale <= 68)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoBoss();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_tiroNaCabeca()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 125;
        max = 175;

        //CHANCE DE ACERTAR
        if(ale <= 53)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoBoss();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerCura_cafePreto()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 90;
        max = 100;

        //CHANCE DE ACERTAR
        if(ale <= 51)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            playerSucesso += 1;

            cura = GeradorRandomico(min, max);
            curaAoPlayer();
        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            playerFalha += 1;
        }

    }

    int PlayerDano_6tiros()
    {
        while(cont < 6)
        {

            cont++;
            porcentagem();

            //DANO || CURA, minimo e maximo
            min = 30;
            max = 70;

            //CHANCE DE ACERTAR
            if(ale <= 45)
            {

                textcolor(11);
                textoSequencial("\nSUCESSO!\n", 75000);
                playerSucesso += 1;

                dano = GeradorRandomico(min, max);
                danoAoBoss();
            }
            else
            {
                textcolor(12);
                textoSequencial("\nFALHA!\n\n", 75000);
                playerFalha += 1;
            }
        }

    }

    int ChancesClasse_Pistoleiro()
    {
        if(escolha == 1)
        {
            PlayerDano_tiroPreciso();
        }
        else if(escolha == 2)
        {
            PlayerDano_arremessoDeFaca();
        }
        else if(escolha == 3)
        {
            PlayerDano_tiroNaCabeca();
        }
        else if(escolha == 4)
        {
            PlayerCura_cafePreto();
        }
        else if(escolha == 5)
        {
            PlayerDano_6tiros();
        }
        else
        {
            textoSequencial("Essa opção nao existe, tente novamente: ", 50000);
            scanf("%d", &escolha);
            ChancesClasse_Pistoleiro();
        }
    }

    // Turno do jogador

    int TurnoPlayer()
    {
        textcolor(13);
        textoSequencial("SEU TURNO:\n", 45000);

        PlayerCuraPassiva();

        if(escolhaclasse == 1)
        {
            TabelaDeHabilidadesClasse_Cavaleiro();
        }
        else if(escolhaclasse == 2)
        {
            TabelaDeHabilidadesClasse_Pistoleiro();
        }
        else if(escolhaclasse == 3)
        {
            TabelaDeHabilidadesClasse_Assassino();
        }

        textcolor(14);
        textoSequencial("Digite qual habilidade voce quer usar: ", 35000);
        scanf("%d", &escolha);

        if(escolhaclasse == 1)
        {
            ChancesClasse_Cavaleiro();
        }
        else if(escolhaclasse == 2)
        {
            ChancesClasse_Pistoleiro();
        }
        else if(escolhaclasse == 3)
        {
            ChancesClasse_Assassino();
        }
    }

    // possiveis ESCOLHAS DO BOSS \/

    int TabelaDeHabilidadesBoss()
    {
        textcolor(15);

        textoSequencial("Quantidade (min e max):  | Nome do ataque:    | Chance de sucesso:\n", 990);
        textoSequencial("(25 - 80)    dano        | Sequência de socos | (94% de chance)\n", 990);
        textoSequencial("(0 - 150)    dano        | Maldição           | (82% de chance)\n", 990);
        textoSequencial("(100 - 150)  cura        | Cura mistica       | (31% de chance)\n", 990);
        textoSequencial("(175 - 240)  dano        | Enfincada maligna  | (26% de chance)\n", 990);
        textoSequencial("(75 - 125)   dano & cura | Roubo de vida      | (25% de chance)\n", 990);
    }

    int BossDano_sequenciaDeSocos()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 25;
        max = 80;

        textcolor(6);
        textoSequencial("\nHABILIDADE UTILIZADA: ", 70000);
        textcolor(9);
        textoSequencial("Sequencia de socos\n", 85000);

        //CHANCE DE ACERTAR
        if(ale <= 94)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            bossSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoPlayer();

        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            bossFalha += 1;
        }

    }

    int BossDano_maldicao()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 0;
        max = 150;

        textcolor(6);
        textoSequencial("\nHABILIDADE UTILIZADA: ", 70000);
        textcolor(9);
        textoSequencial("Maldição\n", 85000);

        //CHANCE DE ACERTAR
        if(ale <= 82)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            bossSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoPlayer();

        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            bossFalha += 1;
        }

    }

    int BossCura_curaMistica()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 100;
        max = 150;

        textcolor(6);
        textoSequencial("\nHABILIDADE UTILIZADA: ", 70000);
        textcolor(9);
        textoSequencial("Cura mistica\n", 85000);

        //CHANCE DE ACERTAR
        if(ale <= 31)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            bossSucesso += 1;

            cura = GeradorRandomico(min, max);
            curaAoBoss();

        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            bossFalha += 1;
        }

    }

    int BossDano_enfincadaMaligna()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 175;
        max = 240;

        textcolor(6);
        textoSequencial("\nHABILIDADE UTILIZADA: ", 70000);
        textcolor(9);
        textoSequencial("Enfincada maligna\n", 85000);

        //CHANCE DE ACERTAR
        if(ale <= 26)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            bossSucesso += 1;

            dano = GeradorRandomico(min, max);
            danoAoPlayer();

        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            bossFalha += 1;
        }
    }

    int BossCD_RouboDeVida()
    {
        porcentagem();

        //DANO || CURA, minimo e maximo
        min = 75;
        max = 125;

        textcolor(6);
        textoSequencial("\nHABILIDADE UTILIZADA: ", 70000);
        textcolor(9);
        textoSequencial("Roubo de vida\n", 85000);

        //CHANCE DE ACERTAR
        if(ale <= 25)
        {

            textcolor(11);
            textoSequencial("\nSUCESSO!\n", 75000);
            bossSucesso += 1;

            dano = GeradorRandomico(min, max);
            cura = dano;

            danoAoPlayer();
            curaAoBoss();

        }
        else
        {
            textcolor(12);
            textoSequencial("\nFALHA!\n\n", 75000);
            bossFalha += 1;
        }
    }

    // aleatorizador que define qual ataque o boss vai usar \/

    int BossEscolha()
    {
        min = 1;
        max = 5;

        escolhaBoss = GeradorRandomico(min, max);
    }

    // Chances de acerto e função do turno do BOSS

    int EscolhaChancesBoss()
    {
        BossEscolha();


        if(escolhaBoss == 1 || vidaP < 71)
        {
            BossDano_sequenciaDeSocos();
        }
        else if(escolhaBoss == 2 || vidaP < 101)
        {
            BossDano_maldicao();
        }
        else if(escolhaBoss == 3)
        {
            BossDano_enfincadaMaligna();
        }
        else if(vidaB < 1651 && escolhaBoss == 4)
        {
            BossCura_curaMistica();
        }
        else if(vidaB < 1676 && escolhaBoss == 5)
        {
            BossCD_RouboDeVida();
        }
        else
        {
            EscolhaChancesBoss();
        }
    }

    int TurnoBoss()
    {
        textcolor(13);
        textoSequencial("TURNO DO BOSS:\n", 45000);

        PlayerVeneno();

        TabelaDeHabilidadesBoss();

        EscolhaChancesBoss();
    }

    int inicioEintroducao()
    {
        textoSequencial("Deseja ver a introducao? (1 = sim) (outro numero = nao)\n: ", 50000);
        scanf("%d", &escolha);

        if(escolha == 1)
        {
            textcolor(11);
            textoSequencial("\nVocê vai jogar um jogo baseado em estrátegia e muita sorte onde você vai enfrentar um inimigo desafiador\n...", 60000);
            textoSequencial("Bom agora que eu te expliquei o conceito do jogo vou te mostrar as opções de classes e habilidades do Boss:\n\n", 50000);

            textoSequencial("...\n\n", 90000);

            //---------------------------------------------------------------------------------------------------------------------------

            textcolor(6);
            textoSequencial("Classe: CAVALEIRO\n", 80000);

            TabelaDeHabilidadesClasse_Cavaleiro();

            textcolor(2);
            textoSequencial("(VIDA MÁXIMA DO CAVALEIRO: 1100)\n\n", 50000);

            textcolor(11);
            textoSequencial("Além dessas habilidades o Caveleiro possui uma habilidade passiva de cura que é ativada no início de cada\n", 50000);
            textoSequencial("turno quando o Cavaleiro não está com a vida máxima: ", 50000);
            textoSequencial("(1 - 5) <- cura.\n\n", 50000);

            textoSequencial("A habilidade de 'USO 5' tem um diferencial que se acertada permite que o Cavaleiro tenha uma chance de 50% \nde bloquear o próximo ataque do Boss caso ele acerte.\n\n", 50000);

            //---------------------------------------------------------------------------------------------------------------------------

            textcolor(6);
            textoSequencial("Classe: PISTOLEIRO\n", 80000);

            TabelaDeHabilidadesClasse_Pistoleiro();

            textcolor(2);
            textoSequencial("(VIDA MÁXIMA DO PISTOLEIRO: 750)\n\n", 50000);

            textcolor(11);
            textoSequencial("Além dessas habilidades o Pistoleiro possui uma habilidade passiva de cura que é ativada no início de cada\n", 50000);
            textoSequencial("turno quando o Pistoleiro não está com a vida máxima: ", 50000);
            textoSequencial("(5 - 10) <- cura.\n\n", 50000);

            textoSequencial("A habilidade de 'USO 5' tem um diferencial que permite ao Pistoleiro efetuar vários ataques em um só turno.\n\n", 50000);

            //---------------------------------------------------------------------------------------------------------------------------

            textcolor(6);
            textoSequencial("Classe: Assassino\n", 80000);

            TabelaDeHabilidadesClasse_Assassino();

            textcolor(2);
            textoSequencial("(VIDA MÁXIMA DO ASSASSINO: 975)\n\n", 50000);

            textcolor(11);
            textoSequencial("Além dessas habilidades o Assassino possui uma habilidade passiva de cura que é ativada no início de cada\n", 50000);
            textoSequencial("turno quando o Pistoleiro não está com a vida máxima: ", 50000);
            textoSequencial("(1 - 5) <- cura.\n\n", 50000);

            textoSequencial("A habilidade de 'USO 3' tem um diferencial que permite ao Assassino efetuar vários ataques em um só turno.\n\n", 50000);

            textoSequencial("A habilidade de 'USO 5' tem um diferencial que se acertada permite ao Assassino além de causar dano e também\n causar +1 de envenenamento com 70% de chance do veneno não ser anulado após causar dano.\n\n", 50000);

            textcolor(2);
            textoSequencial("O veneno tem 3 níveis e tem uma chance de ser anulado perdendo um nível. Cada nível causa um dano e efeitos\n", 50000);
            textoSequencial("negativos que vão ficando mais eficases a cada nível:\n\n", 50000);
            textoSequencial("envenenamento 1: (05 - 30) <- dano || (20%) <- cura perdida (boss) || (05%) <- dano perdido (boss)\n", 50000);
            textoSequencial("envenenamento 2: (10 - 35) <- dano || (25%) <- cura perdida (boss) || (10%) <- dano perdido (boss)\n", 50000);
            textoSequencial("envenenamento 3: (15 - 40) <- dano || (30%) <- cura perdida (boss) || (15%) <- dano perdido (boss)\n\n", 50000);
            //---------------------------------------------------------------------------------------------------------------------------

            textcolor(14);
            textoSequencial("cada vez que acertar um ataque no inimigo estando com qualquer classe você tem 10% de chance de causar um \ndano crítico podendo dobrar todo dano!\n\n", 50000);

            textcolor(6);
            textoSequencial("HABILIDADES DO BOSS:\n", 30000);

            TabelaDeHabilidadesBoss();

            textcolor(2);
            textoSequencial("\n(VIDA MÁXIMA DO BOSS: 1750)\n", 50000);

            textcolor(11);
            textoSequencial("\nO Boss pode causar dano crítico com a mesma intencidade e chance ao jogador.\n", 50000);

        }
    }

    srand(time(NULL));

    inicioEintroducao();

    textcolor(13);
    textoSequencial("\nINICIANDO JOGO...\n\n", 75000);

    textoSequencial("ESCOLHA SUA CLASSE:\n", 60000);
    textoSequencial("<  1 = CAVALEIRO  >\n", 60000);
    textoSequencial("<  2 = PISTOLEIRO >\n", 60000);
    textoSequencial("<  3 = ASSASSINO  >\n: ", 60000);
    scanf("%d", &escolhaclasse);

    if(escolhaclasse > 3 || escolhaclasse < 1)
    {
        textcolor(12);
        textoSequencial("\n\nVOCÊ ESTÁ DE BRINCADEIRA NÉ?!?!?!?!\n", 50000);
        textoSequencial("ADEUS! VOU ENCERRAR O JOGO!!!!", 70000);

        textcolor(6);
        textoSequencial("\n\n\nFIM DE JOGO... \nVERSÃO DO JOGO: 2.6\nCriado em linguagem C feito por Gabriel Miguel Haslinger.\n\nencerrando sessão.", 50000);

        return 0;
    }
    else
    {

        textcolor(11);
        textoSequencial("\n\nBOSS: ", 70000);
        textcolor(15);
        textoSequencial("parece que você derrotou meus lacaios e chegou até aqui, certamente você não teme pela própria vida!", 55000);

        if(escolhaclasse == 1)
        {

            vidaP += 100;

            textcolor(11);
            textoSequencial("\n\nCAVALEIRO: ", 70000);
            textcolor(15);
            textoSequencial("Eu vingarei minha família mesmo que isso me custe a VIDA!", 55000);

        }
        else if(escolhaclasse == 2)
        {

            vidaP -= 250;

            textcolor(11);
            textoSequencial("\n\nPISTOLEIRO: ", 70000);
            textcolor(15);
            textoSequencial("Eu literalmente enchi seus guardas de bala, então por que acha que com você vai ser diferente?", 55000);

            textcolor(11);
            textoSequencial("\n\nBOSS: ", 70000);
            textcolor(15);
            textoSequencial("ARR SEU MALDITO CALE A BOCA!!!", 55000);

        }
        else if(escolhaclasse == 3)
        {

            vidaP -= 25;

            textcolor(11);
            textoSequencial("\n\nASSASSINO: ", 70000);
            textcolor(15);
            textoSequencial("QUANDO ISSO ACABAR SUA CABEÇA ESTARA NO CHÃO, BEM LONGE DO RESTO DO SEU CORPO!", 55000);

            textcolor(11);
            textoSequencial("\n\nBOSS: ", 70000);
            textcolor(15);
            textoSequencial("COMO OUSA ME SUBESTIMAR DESSE JEITO!!!!!", 55000);

        }


        textoSequencial("\n\nA BATALHA COMEÇA!\n\n", 70000);

        while(vidaP >= 1 && vidaB >= 1)
        {

            TurnoPlayer();

            if(vidaB < 1)
            {
                textcolor(6);
                textoSequencial("A MORTE BATEU A PORTA... ", 80000);
                textoSequencial("BOSS ESTÁ MORTO!!!\n\nVITÓRIA DO JOGADOR!!!", 100000);

                textcolor(7);
                textoSequencial("\n\n<JOGADOR>  SUCESSOS: ", 60000);
                printf("%d ", playerSucesso);
                textoSequencial("  ", 20000);
                textoSequencial("FALHAS: ", 60000);
                printf("%d ", playerFalha);
                textoSequencial("  ", 20000);
                textoSequencial("CRÍTICOS CAUSADOS: ", 60000);
                printf("%d \n\n", playerCritico);

                textoSequencial("<BOSS>     SUCESSOS: ", 60000);
                printf("%d ", bossSucesso);
                textoSequencial("  ", 20000);
                textoSequencial("FALHAS: ", 60000);
                printf("%d ", bossFalha);
                textoSequencial("  ", 20000);
                textoSequencial("CRÍTICOS CAUSADOS: ", 60000);
                printf("%d \n\n", bossCritico);

                textcolor(6);
                textoSequencial("\n\n\nFIM DE JOGO... \nVERSÃO DO JOGO: 2.6\nCriado em linguagem C feito por Gabriel Miguel Haslinger.\n\nencerrando sessão.", 50000);

                return 0;
            }

            //--------------------------------------------------------

            TurnoBoss();

            if(vidaP < 1)
            {
                textcolor(6);
                textoSequencial("A MORTE BATEU A PORTA... ", 80000);
                textoSequencial("JOGADOR ESTÁ MORTO!!!\n\nVITÓRIA DO BOSS!!!", 100000);

                textcolor(7);
                textoSequencial("\n\n<JOGADOR>  SUCESSOS: ", 60000);
                printf("%d ", playerSucesso);
                textoSequencial("  ", 20000);
                textoSequencial("FALHAS: ", 60000);
                printf("%d ", playerFalha);
                textoSequencial("  ", 20000);
                textoSequencial("CRÍTICOS CAUSADOS: ", 60000);
                printf("%d \n\n", playerCritico);

                textoSequencial("<BOSS>     SUCESSOS: ", 60000);
                printf("%d ", bossSucesso);
                textoSequencial("  ", 20000);
                textoSequencial("FALHAS: ", 60000);
                printf("%d ", bossFalha);
                textoSequencial("   ", 20000);
                textoSequencial("CRÍTICOS CAUSADOS: ", 60000);
                printf("%d \n\n", bossCritico);

                textcolor(6);
                textoSequencial("\n\n\nFIM DE JOGO... \nVERSÃO DO JOGO: 2.6\nCriado em linguagem C feito por Gabriel Miguel Haslinger.\n\nencerrando sessão.", 50000);

                return 0;
            }

            if(vidaB < 1)
            {
                textcolor(6);
                textoSequencial("A MORTE BATEU A PORTA... ", 80000);
                textoSequencial("BOSS ESTÁ MORTO!!!\n\nVITÓRIA DO JOGADOR!!!", 100000);

                textcolor(7);
                textoSequencial("\n\n<JOGADOR>  SUCESSOS: ", 60000);
                printf("%d ", playerSucesso);
                textoSequencial("  ", 20000);
                textoSequencial("FALHAS: ", 60000);
                printf("%d ", playerFalha);
                textoSequencial("  ", 20000);
                textoSequencial("CRÍTICOS CAUSADOS: ", 60000);
                printf("%d \n\n", playerCritico);

                textoSequencial("<BOSS>     SUCESSOS: ", 60000);
                printf("%d ", bossSucesso);
                textoSequencial("  ", 20000);
                textoSequencial("FALHAS: ", 60000);
                printf("%d ", bossFalha);
                textoSequencial("  ", 20000);
                textoSequencial("CRÍTICOS CAUSADOS: ", 60000);
                printf("%d \n\n", bossCritico);

                textcolor(6);
                textoSequencial("\n\n\nFIM DE JOGO... \nVERSÃO DO JOGO: 2.6\nCriado em linguagem C feito por Gabriel Miguel Haslinger.\n\nencerrando sessão.", 50000);

                return 0;
            }

            defesa = 0;
            cont = 0;
        }
    }

}
