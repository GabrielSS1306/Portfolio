#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUARTOS 100
#define MAX_HOSPEDES 100
#define MAX_RESERVAS 200

typedef struct {
    int id;
    char nome[50];
    char email[50];
} Pessoa;

typedef struct {
    Pessoa base;  // herança simulada
} Funcionario;

typedef struct {
    Pessoa base;
    int reservas_ids[MAX_RESERVAS];
    int num_reservas;
} Hospede;

typedef struct {
    int numero;
    char tipo[30];
    int disponivel;
} Quarto;

typedef struct {
    int id;
    Hospede* hospede;
    Quarto* quarto;
} Reserva;

typedef struct {
    char nome[50];
    Quarto quartos[MAX_QUARTOS];
    int num_quartos;

    Hospede hospedes[MAX_HOSPEDES];
    int num_hospedes;

    Reserva reservas[MAX_RESERVAS];
    int num_reservas;
} Hotel;

void add_quarto(Hotel* hotel, Quarto q) {
    hotel->quartos[hotel->num_quartos] = q;
    hotel->num_quartos++;
    printf("Quarto %d adicionado com sucesso!\n", q.numero);
}

void remover_quarto(Hotel* hotel, int numero) {
    for (int i = 0; i < hotel->num_quartos; i++) {
        if (hotel->quartos[i].numero == numero) {
            for (int j = i; j < hotel->num_quartos - 1; j++)
                hotel->quartos[j] = hotel->quartos[j + 1];
            hotel->num_quartos--;
            printf("Quarto %d removido.\n", numero);
            return;
        }
    }
    printf("Quarto nao encontrado.\n");
}

void registrar_hospede(Hotel* hotel, Hospede h) {
    hotel->hospedes[hotel->num_hospedes] = h;
    hotel->num_hospedes++;
    printf("Hospede %s registrado!\n", h.base.nome);
}

void registrar_reserva(Hotel* hotel, Reserva r) {
    hotel->reservas[hotel->num_reservas] = r;
    hotel->num_reservas++;
}

void cancelar_reserva(Hotel* hotel, int id) {
    for (int i = 0; i < hotel->num_reservas; i++) {
        if (hotel->reservas[i].id == id) {

            // liberar quarto
            hotel->reservas[i].quarto->disponivel = 1;

            // remover reserva
            for (int j = i; j < hotel->num_reservas - 1; j++)
                hotel->reservas[j] = hotel->reservas[j + 1];

            hotel->num_reservas--;
            printf("Reserva cancelada.\n");
            return;
        }
    }
    printf("Reserva nao encontrada.\n");
}

void listar_quartos_disponiveis(Hotel* hotel) {
    int encontrou = 0;

    printf("\n--- QUARTOS DISPONIVEIS ---\n");
    for (int i = 0; i < hotel->num_quartos; i++) {
        if (hotel->quartos[i].disponivel) {
            printf("Quarto %d (%s)\n", hotel->quartos[i].numero, hotel->quartos[i].tipo);
            encontrou = 1;
        }
    }
    if (!encontrou)
        printf("Nenhum quarto disponivel.\n");
}

void status_hotel(Hotel* hotel) {
    printf("\n--- STATUS DO HOTEL ---\n");
    printf("Quartos: %d\n", hotel->num_quartos);
    printf("Hospedes: %d\n", hotel->num_hospedes);
    printf("Reservas ativas: %d\n", hotel->num_reservas);
}

void fazer_reserva(Hotel* hotel, Hospede* hospede, Quarto* quarto) {
    if (!quarto->disponivel) {
        printf("Quarto nao disponivel.\n");
        return;
    }

    Reserva r;
    r.id = hotel->num_reservas + 1;
    r.hospede = hospede;
    r.quarto = quarto;

    quarto->disponivel = 0;

    registrar_reserva(hotel, r);

    hospede->reservas_ids[hospede->num_reservas] = r.id;
    hospede->num_reservas++;

    printf("Reserva realizada para o quarto %d!\n", quarto->numero);
}

void consultar_reservas(Hospede* hospede, Hotel* hotel) {
    if (hospede->num_reservas == 0) {
        printf("Nenhuma reserva encontrada.\n");
        return;
    }

    printf("\nReservas de %s:\n", hospede->base.nome);

    for (int i = 0; i < hospede->num_reservas; i++) {
        int id = hospede->reservas_ids[i];

        for (int j = 0; j < hotel->num_reservas; j++) {
            if (hotel->reservas[j].id == id) {
                printf("- Quarto %d\n", hotel->reservas[j].quarto->numero);
            }
        }
    }
}

int main() {
    Hotel hotel;
    strcpy(hotel.nome, "Hotel C");
    hotel.num_quartos = 0;
    hotel.num_hospedes = 0;
    hotel.num_reservas = 0;

    int opcao;

    while (1) {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Funcionário\n");
        printf("2 - Hospede\n");
        printf("3 - Status do hotel\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            Funcionario f;

            printf("Nome: ");
            fgets(f.base.nome, 50, stdin);
            f.base.nome[strcspn(f.base.nome, "\n")] = 0;

            printf("Email: ");
            fgets(f.base.email, 50, stdin);
            f.base.email[strcspn(f.base.email, "\n")] = 0;

            while (1) {
                printf("\n--- MENU FUNCIONARIO ---\n");
                printf("1 - Adicionar quarto\n");
                printf("2 - Remover quarto\n");
                printf("3 - Registrar hospede\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                if (opcao == 1) {
                    Quarto q;
                    printf("Numero: ");
                    scanf("%d", &q.numero);
                    getchar();

                    printf("Tipo: ");
                    fgets(q.tipo, 30, stdin);
                    q.tipo[strcspn(q.tipo, "\n")] = 0;

                    q.disponivel = 1;
                    add_quarto(&hotel, q);
                }

                else if (opcao == 2) {
                    int num;
                    printf("Numero do quarto: ");
                    scanf("%d", &num);
                    remover_quarto(&hotel, num);
                }

                else if (opcao == 3) {
                    Hospede h;
                    printf("Nome do hospede: ");
                    getchar();
                    fgets(h.base.nome, 50, stdin);
                    h.base.nome[strcspn(h.base.nome, "\n")] = 0;

                    printf("Email: ");
                    fgets(h.base.email, 50, stdin);
                    h.base.email[strcspn(h.base.email, "\n")] = 0;

                    h.num_reservas = 0;

                    registrar_hospede(&hotel, h);
                }

                else if (opcao == 0)
                    break;
            }
        }

        else if (opcao == 2) {
            char email[50];
            printf("Email: ");
            fgets(email, 50, stdin);
            email[strcspn(email, "\n")] = 0;

            Hospede* h = NULL;

            for (int i = 0; i < hotel.num_hospedes; i++) {
                if (strcmp(hotel.hospedes[i].base.email, email) == 0) {
                    h = &hotel.hospedes[i];
                    break;
                }
            }

            if (!h) {
                printf("Hospede nao encontrado.\n");
                continue;
            }

            while (1) {
                printf("\n--- MENU HOSPEDE ---\n");
                printf("1 - Fazer reserva\n");
                printf("2 - Consultar reservas\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);

                if (opcao == 1) {
                    listar_quartos_disponiveis(&hotel);
                    int num;
                    printf("Quarto desejado: ");
                    scanf("%d", &num);

                    Quarto* q = NULL;
                    for (int i = 0; i < hotel.num_quartos; i++) {
                        if (hotel.quartos[i].numero == num)
                            q = &hotel.quartos[i];
                    }

                    if (q)
                        fazer_reserva(&hotel, h, q);
                    else
                        printf("Quarto nao encontrado.\n");
                }

                else if (opcao == 2) {
                    consultar_reservas(h, &hotel);
                }

                else if (opcao == 0)
                    break;
            }
        }

        else if (opcao == 3) {
            status_hotel(&hotel);
        }

        else if (opcao == 0) {
            printf("Saindo...\n");
            break;
        }
    }

    return 0;
}
