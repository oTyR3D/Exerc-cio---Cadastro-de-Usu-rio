#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 1000

typedef struct
{
    int codigo;
    char nomeCompleto[50];
    char email[50];
    char genero;
    char endereco[100];
    double altura;
    int tomouVacina;
} Pessoa;

// Protótipos de funções
void limparBufferEntrada();
int validarFormatoEmail(const char email[]);
void cadastrarUsuario(Pessoa usuarios[], int *totalCadastros);
void imprimirUsuarios(const Pessoa usuarios[], int totalCadastrados);
void buscarPorEmail(const Pessoa usuarios[], int totalCadastros, const char email[]);
void editarUsuario(Pessoa usuarios[], int totalCadastrados, int codigo);
void excluirUsuario(Pessoa usuarios[], int *totalCadastrados, int codigo);

int main()
{
    srand((unsigned int)time(NULL));

    Pessoa usuarios[MAX_USUARIOS];
    int totalCadastros = 0;

    char opcao;

    do
    {
        printf("\nOpções\n");
        printf("1: Cadastrar\n");
        printf("2: Imprimir\n");
        printf("3: Buscar por E-mail\n");
        printf("4: Editar\n");
        printf("5: Excluir\n");
        printf("0: Sair\n");

        printf("Escolha a opção desejada: ");
        scanf(" %c", &opcao);

        switch (opcao)
        {
        case '1':
            cadastrarUsuario(usuarios, &totalCadastros);
            break;
        case '2':
            imprimirUsuarios(usuarios, totalCadastros);
            break;
        case '3':
            printf("Informe o e-mail a ser buscado: ");
            char buscaEmail[50];
            scanf(" %s", buscaEmail);
            buscarPorEmail(usuarios, totalCadastros, buscaEmail);
            break;
        case '4':
            printf("Informe o Código do usuário a ser editado: ");
            int codigoEditar;
            scanf("%d", &codigoEditar);
            editarUsuario(usuarios, totalCadastros, codigoEditar);
            break;
        case '5':
            printf("Informe o Código do usuário a ser excluído: ");
            int codigoExcluir;
            scanf("%d", &codigoExcluir);
            excluirUsuario(usuarios, &totalCadastros, codigoExcluir);
            break;
        case '0':
            printf("Saiu do Programa\n");
            break;
        default:
            printf("Opção inválida! Tente novamente\n");
        }
    } while (opcao != '0');

    return 0;
}

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int validarFormatoEmail(const char email[])
{
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            printf("E-mail validado\n");
            return 1;
        }
    }

    printf("E-mail inválido! Tente novamente\n");
    return 0;
}

void cadastrarUsuario(Pessoa usuarios[], int *totalCadastros)
{
    if (*totalCadastros >= MAX_USUARIOS)
    {
        printf("Limite de usuários atingido.\n");
        return;
    }

    usuarios[*totalCadastros].codigo = rand() % 1000 + 1;

    printf("Informe o nome completo: ");
    limparBufferEntrada();
    fgets(usuarios[*totalCadastros].nomeCompleto, sizeof(usuarios[*totalCadastros].nomeCompleto), stdin);
    usuarios[*totalCadastros].nomeCompleto[strcspn(usuarios[*totalCadastros].nomeCompleto, "\n")] = '\0';

    while (!validarFormatoEmail(usuarios[*totalCadastros].email))
    {
        printf("Informe o e-mail:");
        fgets(usuarios[*totalCadastros].email, sizeof(usuarios[*totalCadastros].email), stdin);
        usuarios[*totalCadastros].email[strcspn(usuarios[*totalCadastros].email, "\n")] = '\0';
    }

    printf("Informe o gênero (M, F ou I): ");
    scanf(" %c", &usuarios[*totalCadastros].genero);

    printf("Informe o endereço:");
    limparBufferEntrada();
    fgets(usuarios[*totalCadastros].endereco, sizeof(usuarios[*totalCadastros].endereco), stdin);
    usuarios[*totalCadastros].endereco[strcspn(usuarios[*totalCadastros].endereco, "\n")] = '\0';

    printf("Informe a altura: ");
    scanf("%lf", &usuarios[*totalCadastros].altura);

    printf("Informe se tomou a vacina (1 para sim, 0 para não): ");
    scanf("%d", &usuarios[*totalCadastros].tomouVacina);

    (*totalCadastros)++;
}

void imprimirUsuarios(const Pessoa usuarios[], int totalCadastrados)
{
    if (totalCadastrados == 0)
    {
        printf("Cadastro de usuários vazio\n");
        return;
    }

    printf("\nLista de Usuários\n");
    for (int i = 0; i < totalCadastrados; i++)
    {
        printf("Código: %d\n", usuarios[i].codigo);
        printf("Nome: %s\n", usuarios[i].nomeCompleto);
        printf("Email: %s\n", usuarios[i].email);
        printf("Gênero: %c\n", usuarios[i].genero);
        printf("Endereço: %s\n", usuarios[i].endereco);
        printf("Altura: %.2lf metros\n", usuarios[i].altura);
        printf("Vacina: %s\n", usuarios[i].tomouVacina ? "Tomou" : "Não tomou");
        printf("\n");
    }
}

void buscarPorEmail(const Pessoa usuarios[], int totalCadastros, const char email[])
{
    if (totalCadastros == 0)
    {
        printf("Cadastro de usuários vazio\n");
        return;
    }

    int encontrado = 0;

    for (int i = 0; i < totalCadastros; i++)
    {
        if (strcmp(usuarios[i].email, email) == 0)
        {
            printf("Usuário Encontrado:\n");
            printf("Código: %d\n", usuarios[i].codigo);
            printf("Nome: %s\n", usuarios[i].nomeCompleto);
            printf("Email: %s\n", usuarios[i].email);
            printf("Gênero: %c\n", usuarios[i].genero);
            printf("Endereço: %s\n", usuarios[i].endereco);
            printf("Altura: %.2lf metros\n", usuarios[i].altura);
            printf("Vacina: %s\n", usuarios[i].tomouVacina ? "Tomou" : "Não tomou");
            printf("\n");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Usuário com o e-mail %s não encontrado.\n", email);
    }
}

void editarUsuario(Pessoa usuarios[], int totalCadastrados, int codigo)
{
    printf("Editando usuário Código %d\n", codigo);

    for (int i = 0; i < totalCadastrados; i++)
    {
        if (usuarios[i].codigo == codigo)
        {
            int opcao;

            do
            {
                printf("\nEscolha a opção que deseja editar\n");
                printf("1: Nome completo\n");
                printf("2: E-mail\n");
                printf("3: Gênero\n");
                printf("4: Endereço\n");
                printf("5: Altura\n");
                printf("6: Vacina\n");
                printf("7: Alterar cadastro inteiro\n");
                printf("0: Sair\n");
                printf("Opção:");
                scanf("%d", &opcao);

                switch (opcao)
                {
                case 1:
                    printf("Informe o novo nome completo:");
                    limparBufferEntrada();
                    fgets(usuarios[i].nomeCompleto, sizeof(usuarios[i].nomeCompleto), stdin);
                    usuarios[i].nomeCompleto[strcspn(usuarios[i].nomeCompleto, "\n")] = '\0';
                    break;
                case 2:
                    printf("Informe o novo e-mail (ou '0' para sair): ");
                    limparBufferEntrada();
                    fgets(usuarios[i].email, sizeof(usuarios[i].email), stdin);
                    usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';
                    if (strcmp(usuarios[i].email, "0") == 0)
                    {
                        break; // Sair da edição de e-mail
                    }
                    while (!validarFormatoEmail(usuarios[i].email))
                    {
                        printf("Informe o novo e-mail (ou '0' para sair): ");
                        fgets(usuarios[i].email, sizeof(usuarios[i].email), stdin);
                        usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';
                        if (strcmp(usuarios[i].email, "0") == 0)
                        {
                            break; // Sair da edição de e-mail
                        }
                    }
                    break;
                case 3:
                    printf("Informe o novo gênero (M/F/I): ");
                    limparBufferEntrada();
                    scanf(" %c", &usuarios[i].genero);
                    break;
                case 4:
                    printf("Informe o novo endereço:");
                    limparBufferEntrada();
                    fgets(usuarios[i].endereco, sizeof(usuarios[i].endereco), stdin);
                    usuarios[i].endereco[strcspn(usuarios[i].endereco, "\n")] = '\0';
                    break;
                case 5:
                    printf("Informe a nova altura:");
                    scanf("%lf", &usuarios[i].altura);
                    break;
                case 6:
                    printf("Informe se tomou a vacina (1 para sim, 0 para não): ");
                    scanf("%d", &usuarios[i].tomouVacina);
                    break;
                case 7:
                    printf("\nEditando cadastro inteiro do Usuário Código %d\n", codigo);
                    cadastrarUsuario(usuarios, &totalCadastrados);
                    return;
                case 0:
                    printf("Saindo da edição.\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (opcao != 0);

            printf("Cadastro atualizado com sucesso!\n");
            return;
        }
    }

    printf("Usuário Código %d não encontrado!\n", codigo);
}

void excluirUsuario(Pessoa usuarios[], int *totalCadastrados, int codigo)
{
    if (*totalCadastrados == 0)
    {
        printf("Cadastro de usuários vazio\n");
        return;
    }

    for (int i = 0; i < *totalCadastrados; i++)
    {
        if (usuarios[i].codigo == codigo)
        {
            for (int j = i; j < *totalCadastrados - 1; j++)
            {
                usuarios[j] = usuarios[j + 1];
            }
            (*totalCadastrados)--;
            printf("Usuário Código %d excluído com sucesso!\n", codigo);
            return;
        }
    }

    printf("Usuário Código %d não encontrado!\n", codigo);
}
