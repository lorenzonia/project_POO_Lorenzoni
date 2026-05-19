
# Análise orientada a objeto

> [!NOTE]
> A **análise orientada a objeto** consiste na descrição do problema a ser tratado, incluindo a definição dos casos de uso e a modelagem conceitual do domínio do sistema.

---

## 1. Descrição Geral do Domínio do Problema

Este projeto tem como objetivo o desenvolvimento de uma aplicação para simulação de uma **máquina de tração e compressão**, utilizando uma interface gráfica baseada em Qt e implementada em C++.

A máquina simulada representa o comportamento de um cilindro pneumático, sendo capaz de executar movimentos de avanço (compressão) e retorno (tração). Como não haverá sensores físicos na implementação final, os dados de operação (força, pressão e posição) serão gerados de forma simulada, dentro de intervalos realistas.

O sistema deve permitir que o usuário controle e monitore a operação da máquina de forma interativa.

### 🔧 Funcionalidades principais:

1. Operar nos modos:
   - Tração
   - Compressão  

2. Operar em:
   - Modo manual  
   - Modo automático  

3. Monitorar:
   - Posição do cilindro  
   - Força aplicada  

4. Controlar:
   - Velocidade do movimento  
   - Direção (avanço/retorno)  

5. Exibir uma interface gráfica com:
   - Controles de operação  
   - Visualização de dados em tempo real  

6. Simular sensores:
   - Força  
   - Pressão  
   - Posição  

---

## 2. Atores do Sistema

Os atores representam entidades externas que interagem com o sistema.

- **Usuário**: operador da máquina, responsável por controlar e monitorar sua execução.

---

## 3. Diagrama de Casos de Uso

```mermaid
flowchart LR

User[Usuário]

User --> UC1[Selecionar modo (Manual/Automático)]
User --> UC2[Selecionar operação (Tração/Compressão)]
User --> UC3[Ajustar velocidade]
User --> UC4[Iniciar operação]
User --> UC5[Parar operação]
User --> UC6[Monitorar dados]

Sistema[Sistema]

Sistema --> UC7[Simular sensores]
Sistema --> UC8[Atualizar interface]
Sistema --> UC9[Verificar limites]
