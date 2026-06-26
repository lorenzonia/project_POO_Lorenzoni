# Testes

Esta seção descreve o processo de testes realizados no sistema, com o objetivo de validar o funcionamento das funcionalidades implementadas e garantir a consistência do comportamento da aplicação.

---

## 1. Objetivo dos Testes

Os testes tiveram como finalidade:

- verificar o funcionamento correto dos modos de operação
- validar a máquina de estados do ensaio
- garantir consistência entre interface e lógica interna
- avaliar o comportamento do modelo físico
- identificar e corrigir possíveis falhas de interação

---

## 2. Metodologia de Testes

Os testes foram realizados de forma manual, por meio da execução da aplicação e interação direta com a interface gráfica.

Cada funcionalidade foi testada isoladamente e em conjunto, observando:

- resposta da interface
- comportamento do sistema ao longo do tempo
- consistência dos valores apresentados
- transições de estado do ensaio

---

## 3. Testes Realizados

### 3.1 ▶️ Inicialização do Sistema

**Descrição:**
Verificação do comportamento da aplicação ao iniciar.

**Procedimento:**
- Abrir a aplicação
- Verificar estado inicial da interface

**Resultado esperado:**
- modo manual ativo
- sliders habilitados
- grupo de ensaio oculto

**Resultado obtido:**
- comportamento conforme esperado

---

### 3.2 ▶️ Modo Manual

**Descrição:**
Validação do controle manual do sistema.

**Procedimento:**
- Selecionar modo manual
- Ajustar sliders de pressão e vazão
- Observar movimento do cilindro

**Resultado esperado:**
- movimento proporcional aos valores definidos
- atualização contínua da interface

**Resultado obtido:**
- comportamento consistente com os dados de entrada

---

### 3.3 ▶️ Modo Automático

**Descrição:**
Verificação do funcionamento do controle automático.

**Procedimento:**
- Selecionar modo automático
- Definir parâmetros de ensaio
- Iniciar o sistema

**Resultado esperado:**
- execução automática da aproximação
- transição para teste ao atingir o objeto

**Resultado obtido:**
- máquina de estados funcionando corretamente

---

### 3.4 ▶️ Máquina de Estados

**Descrição:**
Validação das transições entre estados do ensaio.

**Procedimento:**
- Executar ensaio automático
- Monitorar mudança de estados

**Resultado esperado:**
- Aproximacao → Teste → Finalizado

**Resultado obtido:**
- transições corretas conforme posição do cilindro

---

### 3.5 ▶️ Lógica de Contato

**Descrição:**
Testar o cálculo do ponto de contato com o objeto.

**Procedimento:**
- Definir diferentes alturas de objeto
- Executar ensaio

**Resultado esperado:**
- compressão: contato em (deslocamentoMaximo - altura)
- tração: contato em (altura)

**Resultado obtido:**
- posicionamento correto nos dois modos

---

### 3.6 ▶️ Controle Híbrido

**Descrição:**
Validação do ajuste manual durante o teste automático.

**Procedimento:**
- iniciar ensaio automático
- alterar pressão via slider na fase de teste

**Resultado esperado:**
- sistema assume valor do slider
- campo de pressão sincroniza

**Resultado obtido:**
- comportamento consistente e estável

---

### 3.7 ▶️ Reset do Sistema

**Descrição:**
Verificação da funcionalidade de reinicialização.

**Procedimento:**
- executar ensaio
- acionar botão reset

**Resultado esperado:**
- posição reiniciada
- estado retorna para Aproximacao
- gráfico limpo

**Resultado obtido:**
- sistema reinicia corretamente

---

### 3.8 ▶️ Gráfico em Tempo Real

**Descrição:**
Validação da atualização do gráfico.

**Procedimento:**
- executar ensaio contínuo
- observar gráfico

**Resultado esperado:**
- incremento contínuo dos dados
- escala ajustada automaticamente

**Resultado obtido:**
- gráfico apresenta comportamento consistente

---

## 4. Problemas Identificados e Correções

Durante os testes, alguns problemas foram identificados:

- inconsistência entre campo de pressão e slider  
- comportamento incorreto no reset em diferentes direções  
- divergência na lógica de contato em tração  

Esses problemas foram corrigidos por meio de:

- sincronização de variáveis de setpoint
- ajuste da lógica de reset
- correção do cálculo de posição de contato

---

## 5. Resultado Geral dos Testes

Os testes indicaram que o sistema apresenta:

- comportamento consistente
- funcionamento correto das funcionalidades
- integração adequada entre interface e lógica
- estabilidade durante execução contínua

---

## 6. Limitações

Apesar dos resultados satisfatórios, algumas limitações foram observadas:

- ausência de testes automatizados
- modelo físico simplificado
- concentração de lógica na interface

---

## 7. Considerações Finais

O processo de testes permitiu validar de forma consistente o funcionamento das principais funcionalidades do sistema, abrangendo tanto o modo de operação manual quanto o automático.

A execução dos testes possibilitou verificar o comportamento da máquina de estados, garantindo transições corretas entre os estados de "Aproximacao, Teste e Finalizado", bem como a coerência do fluxo operacional durante a realização do ensaio.

Além disso, foi possível confirmar a consistência do modelo físico implementado, incluindo os cálculos de força, velocidade e posição, e a correta aplicação da lógica de contato entre o cilindro e o objeto de ensaio, tanto em operações de compressão quanto de tração.

Durante os testes, também foram identificadas e corrigidas inconsistências relacionadas à sincronização entre a interface gráfica e a lógica interna do sistema, especialmente no controle de pressão e no comportamento do reset. Essas correções contribuíram significativamente para a estabilidade e previsibilidade da aplicação.

A validação da atualização em tempo real da interface, incluindo o gráfico e a visualização do cilindro, demonstrou a adequada integração entre os componentes do sistema e a responsividade da aplicação durante a execução contínua.

De forma geral, os resultados obtidos indicam que o sistema atende aos requisitos propostos, apresentando comportamento consistente, funcionamento estável e uma simulação coerente do ensaio de tração e compressão, constituindo uma base sólida para futuras melhorias e expansões.


<div align="center">

[Retroceder](implementacao.md) | [Início](README.md)

</div>