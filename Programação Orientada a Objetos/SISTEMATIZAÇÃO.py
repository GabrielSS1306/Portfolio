class Pessoa:
    def __init__(self, id, nome, email):
        self._id = id
        self._nome = nome
        self._email = email

    def get_id(self):
        return self._id

    def get_nome(self):
        return self._nome

    def get_email(self):
        return self._email

class Funcionario(Pessoa):
    def add_quarto(self, hotel, quarto):
        hotel.add_quarto(quarto)
        print(f"Funcionário adicionou o quarto {quarto.get_numero()} ao hotel.")

    def remover_quarto(self, hotel, quarto):
        hotel.remover_quarto(quarto)
        print(f"Quarto {quarto.get_numero()} foi removido do hotel.")

    def registrar_hospede(self, hotel, hospede):
        hotel.registrar_hospede(hospede)
        print(f"Hóspede {hospede.get_nome()} foi registrado no hotel.")

    def cancelar_reserva(self, hotel, reserva):
        hotel.cancelar_reserva(reserva)
        print("Reserva cancelada com sucesso.")

class Hospede(Pessoa):
    def __init__(self, id, nome, email):
        super().__init__(id, nome, email)
        self._reservas = []

    def fazer_reserva(self, hotel, quarto):
        if quarto.estaDisponivel():
            reserva = Reserva(self, quarto)
            self._reservas.append(reserva)
            hotel.registrar_reserva(reserva)
            quarto.reservar()
            print(f"Reserva feita com sucesso para o quarto {quarto.get_numero()}.")
        else:
            print("Quarto não está disponível.")

    def cancelar_reserva(self, hotel, reserva):
        if reserva in self._reservas:
            self._reservas.remove(reserva)
            hotel.cancelar_reserva(reserva)
            reserva._quarto.liberar()
            print("Reserva cancelada com sucesso.")
        else:
            print("Reserva não encontrada para este hóspede.")

    def consultar_reservas(self):
        if not self._reservas:
            print("Nenhuma reserva encontrada.")
        else:
            print(f"Reservas de {self._nome}:")
            for r in self._reservas:
                print(f" - Quarto {r._quarto.get_numero()}")

class Quarto:
    def __init__(self, numero, tipo):
        self._numero = numero
        self._tipo = tipo
        self._disponivel = True

    def get_numero(self):
        return self._numero

    def get_tipo(self):
        return self._tipo

    def estaDisponivel(self):
        return self._disponivel

    def reservar(self):
        if self._disponivel:
            self._disponivel = False
        else:
            print("Quarto já está reservado.")

    def liberar(self):
        self._disponivel = True

class Reserva:
    total_reservas = 0 

    def __init__(self, hospede, quarto):
        self._hospede = hospede
        self._quarto = quarto
        Reserva.total_reservas += 1

    @classmethod
    def get_total_reservas(cls):
        return cls.total_reservas

class Hotel:
    def __init__(self, nome):
        self._nome = nome
        self._quartos = []
        self._hospedes = []
        self._reservas = []

    def add_quarto(self, quarto):
        self._quartos.append(quarto)

    def remover_quarto(self, quarto):
        if quarto in self._quartos:
            self._quartos.remove(quarto)

    def registrar_hospede(self, hospede):
        self._hospedes.append(hospede)

    def registrar_reserva(self, reserva):
        self._reservas.append(reserva)

    def cancelar_reserva(self, reserva):
        if reserva in self._reservas:
            self._reservas.remove(reserva)

    def listar_quartos_disponiveis(self):
        disponiveis = [q for q in self._quartos if q.estaDisponivel()]
        if not disponiveis:
            print("Nenhum quarto disponível no momento.")
        else:
            print(f"Quartos disponíveis no {self._nome}:")
            for q in disponiveis:
                print(f" - Quarto {q.get_numero()} ({q.get_tipo()})")
        return disponiveis

    def status_hotel(self):
        print(f"\n STATUS DO HOTEL: {self._nome}")
        print(f"Quartos totais: {len(self._quartos)}")
        print(f"Hóspedes registrados: {len(self._hospedes)}")
        print(f"Reservas ativas: {len(self._reservas)}")
        print(f"Total geral de reservas feitas: {Reserva.get_total_reservas()}")

def menu():
    hotel = Hotel("")

    funcionarios = []
    hospedes = []

    print("Seja bem vindo ao nosso hotel! Para começarmos sua reserva, presisaremos de algumas informações básicas a seguir.")
    while True:
        print("\nSelecione o tipo de usuário:")
        print("1 - Funcionário")
        print("2 - Hóspede")
        print("3 - Ver status do hotel")
        print("0 - Sair")
        usuario = input("Escolha: ")

        if usuario == "1":
            nome = input("Nome do funcionário: ")
            email = input("Email: ")
            id_func = len(funcionarios) + 1
            f = Funcionario(id_func, nome, email)
            funcionarios.append(f)

            while True:
                print("\n--- MENU FUNCIONÁRIO ---")
                print("1 - Adicionar quarto")
                print("2 - Remover quarto")
                print("3 - Registrar hóspede")
                print("4 - Cancelar reserva")
                print("0 - Voltar ao menu principal")
                escolha = input("Escolha: ")

                if escolha == "1":
                    numero = int(input("Número do quarto: "))
                    tipo = input("Tipo do quarto (simples, luxo, etc): ")
                    quarto = Quarto(numero, tipo)
                    f.add_quarto(hotel, quarto)

                elif escolha == "2":
                    numero = int(input("Número do quarto a remover: "))
                    quarto = next((q for q in hotel._quartos if q.get_numero() == numero), None)
                    if quarto:
                        f.remover_quarto(hotel, quarto)
                    else:
                        print("Quarto não encontrado.")

                elif escolha == "3":
                    nome_h = input("Nome do hóspede: ")
                    email_h = input("Email: ")
                    id_h = len(hospedes) + 1
                    hospede = Hospede(id_h, nome_h, email_h)
                    f.registrar_hospede(hotel, hospede)
                    hospedes.append(hospede)

                elif escolha == "4":
                    if not hotel._reservas:
                        print("Nenhuma reserva para cancelar.")
                    else:
                        hotel.status_hotel()
                        num = int(input("Digite o número do quarto da reserva a cancelar: "))
                        reserva = next((r for r in hotel._reservas if r._quarto.get_numero() == num), None)
                        if reserva:
                            f.cancelar_reserva(hotel, reserva)
                        else:
                            print("Reserva não encontrada.")

                elif escolha == "0":
                    break
                else:
                    print("Opção inválida!")

        elif usuario == "2":
            if not hospedes:
                print("Nenhum hóspede registrado. Peça a um funcionário para registrá-lo primeiro.")
                continue

            email = input("Digite seu email para login: ")
            hospede = next((h for h in hospedes if h.get_email() == email), None)

            if not hospede:
                print("Hóspede não encontrado.")
                continue

            while True:
                print("\n--- MENU HÓSPEDE ---")
                print("1 - Fazer reserva")
                print("2 - Cancelar reserva")
                print("3 - Consultar reservas")
                print("0 - Voltar ao menu principal")
                escolha = input("Escolha: ")

                if escolha == "1":
                    disponiveis = hotel.listar_quartos_disponiveis()
                    if disponiveis:
                        num = int(input("Digite o número do quarto que deseja reservar: "))
                        quarto = next((q for q in disponiveis if q.get_numero() == num), None)
                        if quarto:
                            hospede.fazer_reserva(hotel, quarto)
                        else:
                            print("Quarto inválido.")

                elif escolha == "2":
                    if not hospede._reservas:
                        print("Você não possui reservas.")
                    else:
                        hospede.consultar_reservas()
                        num = int(input("Digite o número do quarto que deseja cancelar: "))
                        reserva = next((r for r in hospede._reservas if r._quarto.get_numero() == num), None)
                        if reserva:
                            hospede.cancelar_reserva(hotel, reserva)
                        else:
                            print("Reserva não encontrada.")

                elif escolha == "3":
                    hospede.consultar_reservas()

                elif escolha == "0":
                    break
                else:
                    print("Opção inválida!")


        elif usuario == "3":
            hotel.status_hotel()

        elif usuario == "0":
            print("Até logo!")
            break
        else:
            print("Opção inválida! Escolha novamente.")

if __name__ == "__main__":
    menu()