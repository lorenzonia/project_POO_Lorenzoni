# Implementação

Esta seção descreve o processo de desenvolvimento do sistema, detalhando as tecnologias utilizadas, as principais decisões técnicas e a forma como o modelo proposto foi implementado em código.

---

## 1. Linguagem e Ferramentas

O sistema foi desenvolvido utilizando as seguintes tecnologias:

- **Linguagem:** C++
- **Framework:** Qt (Qt Widgets)
- **Gráficos:** QCustomPlot
- **Ambiente de desenvolvimento:** Qt Creator
- **Controle de versão:** Git e GitHub

O uso do framework Qt permitiu a construção de uma interface gráfica interativa, além de fornecer mecanismos como sinais e slots para comunicação entre os componentes.

---

## 2. Estrutura da Implementação

A implementação foi organizada em classes, seguindo os conceitos definidos na etapa de projeto. As principais classes são:

- **MainWindow:** responsável pela interface gráfica e pela lógica principal do sistema
- **Controller:** responsável pelo controle do ciclo de execução
- **SensorSimulator:** responsável pela simulação de ruído nos sinais
- **SensorData:** estrutura para transporte de dados
- **CilindroView:** responsável pela representação visual do cilindro

Apesar da separação proposta, parte da lógica do sistema foi concentrada na classe MainWindow, responsável por integrar os componentes e controlar o comportamento do ensaio.

---

## 3. Interface Gráfica

A interface gráfica foi implementada utilizando Qt Widgets, sendo composta por:

- Botões de controle (Iniciar, Parar, Reset)
- Sliders para ajuste de pressão e vazão
- Campos de entrada para configuração do ensaio
- Seleção de modo de operação (Manual e Automático)
- Visualização do cilindro (CilindroView)
- Gráfico de força ao longo do tempo (QCustomPlot)

A interface permite ao usuário interagir com o sistema e acompanhar o ensaio em tempo real.

---

## 4. Controle do Sistema

O controle de execução é realizado pela classe Controller, que utiliza um mecanismo de atualização periódica baseado em sinais.

O fluxo de execução ocorre da seguinte forma:

- O usuário aciona o início do sistema
- O Controller inicia o ciclo de execução
- Sinais são emitidos continuamente
- A MainWindow recebe esses sinais e executa a atualização da interface

Esse modelo permite desacoplar o gatilho de execução da lógica principal do sistema.

---

## 5. Máquina de Estados

O sistema implementa uma máquina de estados para controle do ensaio automático.

Os estados definidos são:

- **Aproximacao:** movimentação inicial até o contato com o objeto  
- **Teste:** aplicação de carga com controle de pressão  
- **Finalizado:** encerramento da execução  

A transição entre estados ocorre com base na posição do cilindro e nas condições do sistema, garantindo um comportamento previsível e organizado.

---

## 6. Modelo Físico

O comportamento do sistema foi modelado com base em relações físicas simplificadas.

### Força:

Para o cálculo da força, foi utilizada a relação de entre pressão e área (F=P*A).

### Velocidade:

Para determinar a velocidade com que o cilindro se movimenta, foi utilizada a equação (v = vazao / area).

### Conversões:

- pressão (bar → Pa)
- vazão (L/min → m³/s)
- velocidade (m/s → mm por ciclo)

A posição do cilindro é atualizada continuamente com base na velocidade calculada.

---

## 7. Lógica de Contato

O sistema calcula dinamicamente o ponto de contato com o objeto de ensaio.

- **Compressão:**
    - posicao = deslocamentoMaximo - alturaObjeto;
- **Tração:**
    - posicao = alturaObjeto;

Ao atingir essa posição:
- o movimento é limitado
- o estado do ensaio é atualizado

Essa abordagem garante maior realismo na simulação.

---

## 8. Simulação de Sensores

A classe SensorSimulator é responsável por simular medições reais, aplicando ruído aos valores calculados:

- força  
- pressão  
- posição  

Essa simulação permite aproximar o comportamento do sistema ao de um ambiente real.

---

## 9. Atualização da Interface

A função `atualizarInterface()` é responsável por:

- executar a lógica do ensaio
- atualizar os valores simulados
- atualizar o gráfico
- atualizar a posição do cilindro
- sincronizar os controles da interface

Essa função é chamada continuamente durante a execução do sistema.

---

## 10. Controle Híbrido

No modo automático, o sistema adota um controle híbrido:

- **Aproximação:** controle automático  
- **Teste:** controle manual da pressão via slider  

O valor da pressão é sincronizado entre:

- campo de entrada
- slider
- variável interna (setpoint)

---

## 11. Reset e Controle de Execução

O sistema permite:

- **Parar o ensaio:** interrompendo o loop de execução  
- **Resetar:** reiniciando posição, estado e gráfico  

Essas funcionalidades permitem a execução de múltiplos ensaios de forma contínua.

---

## 12. Considerações sobre a Implementação

A implementação resultou em um sistema funcional e coerente com o modelo proposto.  

Apesar disso, algumas melhorias podem ser realizadas:

- maior separação entre interface e lógica
- refinamento do modelo físico
- inclusão de novas funcionalidades
- integração com hardware real

---

## 13. Resultado

A aplicação final apresenta:

- simulação completa do ensaio mecânico
- controle manual e automático
- interface interativa
- atualização em tempo real

O sistema atende aos objetivos do projeto e fornece uma base sólida para futuras expansões.

<div align="center">

[Retroceder](projeto.md) | [Avançar](testes.md)

</div>