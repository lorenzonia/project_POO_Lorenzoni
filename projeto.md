# Projeto orientado a objeto

> Esta etapa descreve a solução proposta para o sistema, a partir da análise previamente realizada, detalhando a estrutura das classes, suas responsabilidades e interações.

---

## 1. Visão Geral da Arquitetura

O sistema foi projetado com base nos princípios da Programação Orientada a Objetos, buscando uma separação clara de responsabilidades entre os componentes.

A arquitetura adotada segue uma abordagem semelhante ao padrão **Model-View-Controller (MVC)**, com as seguintes divisões:

- **View (Interface)**: responsável pela interação com o usuário  
- **Controller (Controle)**: responsável pela lógica da aplicação  
- **Model (Dados/Simulação)**: responsável pela representação e geração dos dados  

Essa separação permite maior organização, facilidade de manutenção e escalabilidade.

---

## 2. Diagrama de Classes

O diagrama de classes apresenta a estrutura estática do sistema, incluindo classes, atributos, métodos e relacionamentos.

![Diagrama de Classes](./docs/UML/Diagrama_Classe_R00.png)

---

## 3. Descrição das Classes

### --> MAinWindow (Interface)

Responsável pela interface gráfica do sistema.

**Atributos:**
- modo: ModoOperacao  
- tipo: TipoOperacao  
- velocidade: float  

**Métodos:**
- iniciarSistema()  
- pararSistema()  
- atualizarInterface(dados: SensorData)  

**Responsabilidade:**
- Receber comandos do usuário  
- Exibir informações do sistema  

---

### --> Controller

Responsável pelo controle da aplicação.

**Atributos:**
- simulador: SensorSimulator  
- cilindro: Cilindro  
- emExecucao: bool  

**Métodos:**
- start()  
- stop()  
- processarDados()  
- verificarLimites(dados: SensorData): bool  

**Responsabilidade:**
- Coordenar o funcionamento do sistema  
- Controlar o fluxo de execução  
- Validar dados  

---

### --> SensorSimulator

Responsável pela simulação dos sensores.

**Métodos:**
- gerarForca(): float  
- gerarPressao(): float  
- gerarPosicao(): float  
- gerarDados(): SensorData  

**Responsabilidade:**
- Gerar valores simulados realistas  
- Substituir sensores físicos  

---

### --> SensorData

Classe responsável por armazenar os dados do sistema.

**Atributos:**
- forca: float  
- pressao: float  
- posicao: float  
- timestamp: datetime  

**Responsabilidade:**
- Transportar dados entre os componentes  

---

### --> Cilindro

Representa o comportamento do atuador da máquina.

**Atributos:**
- posicao: float  
- velocidade: float  
- direcao: TipoOperacao  

**Métodos:**
- avancar()  
- retornar()  
- parar()  

**Responsabilidade:**
- Simular o movimento do cilindro  
- Representar o estado físico do sistema  

---

### --> Enumerações

#### ModoOperacao
Define o modo de operação do sistema:
- MANUAL  
- AUTOMATICO  

#### TipoOperacao
Define o tipo de movimento:
- TRACAO  
- COMPRESSAO  

---

## 4. Relacionamentos entre Classes

- A classe **MainWindow** interage com o **Controller** para iniciar e parar o sistema  
- O **Controller** utiliza o **SensorSimulator** para obter dados simulados  
- O **Controller** controla o **Cilindro**, representando o estado da máquina  
- Os dados gerados são encapsulados na classe **SensorData**  
- A interface utiliza os dados para atualização visual  

Essa estrutura reduz o acoplamento e melhora a organização do sistema.

---

## 5. Diagrama de Sequência

O diagrama de sequência representa a interação entre os componentes ao longo do tempo.

![Diagrama de Sequencia](./docs/UML/Diagrama_Sequencia_R00.png)

### Descrição

1. O usuário inicia o sistema através da interface  
2. O Controller inicia o processo de execução  
3. O SensorSimulator gera dados continuamente  
4. O Controller processa os dados  
5. Os limites são verificados  
6. Os dados são enviados para a interface  
7. O ciclo se repete até que o sistema seja interrompido  

---

## 6. Diagrama de Atividades

O diagrama de atividades apresenta o fluxo de execução do sistema.

![Diagrama de Atividades](./docs/UML/Diagrama_Atividades_R00.png)

### Descrição

O fluxo do sistema segue as seguintes etapas:

1. Configuração inicial  
2. Início da operação  
3. Geração de dados simulados  
4. Processamento dos dados  
5. Verificação de limites  
6. Atualização da interface  
7. Repetição do ciclo  
8. Encerramento do sistema  

---

## 7. Decisões de Projeto

Durante o desenvolvimento do modelo, algumas decisões foram tomadas:

### ✅ Uso de simulação de sensores
Devido à ausência de hardware real, os valores são gerados artificialmente, mantendo comportamentos esperados.

### ✅ Separação de responsabilidades
Cada classe possui uma função específica, reduzindo o acoplamento.

### ✅ Uso de enumerações
Facilita a leitura e evita erros relacionados a valores inválidos.

### ✅ Arquitetura baseada em MVC
Permite melhor organização e facilita futuras expansões.

---

## 8. Considerações Finais

O modelo proposto organiza de forma clara os componentes do sistema, permitindo uma implementação estruturada e coerente em C++ utilizando Qt.

Os diagramas apresentados servem como base para a próxima etapa, que corresponde à implementação do sistema.

---

<div align=center>

[Voltar](analise.md) | [Avançar](implementacao.md)

</div>
