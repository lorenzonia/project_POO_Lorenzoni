#include "Cilindro.h"

// Construtor
Cilindro::Cilindro()
    : posicao(0.0), velocidade(1.0)
{
}

// Movimento para frente (compressão)
void Cilindro::avancar()
{

    direcao = Direcao::AVANCANDO;
    posicao += velocidade;


    if (posicao > 500.0)
        posicao = 500.0;
}

// Movimento para trás (tração)
void Cilindro::retornar()
{
    posicao -= velocidade;

    if (posicao < 0.0)
        posicao = 0.0;
}

// Parar movimento
void Cilindro::parar()
{
    velocidade = 0.0;
}

// Getters
float Cilindro::getPosicao() const
{
    return posicao;
}

float Cilindro::getVelocidade() const
{
    return velocidade;
}

// Setter
void Cilindro::setVelocidade(float v)
{
    velocidade = v;
}