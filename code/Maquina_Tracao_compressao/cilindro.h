#ifndef CILINDRO_H
#define CILINDRO_H

// Declaração do enum antes da classe
enum class Direcao {
    PARADO,
    AVANCANDO,
    RETORNANDO
};

class Cilindro
{
public:
    Cilindro();

    void avancar();
    void retornar();
    void parar();

    float getPosicao() const;
    float getVelocidade() const;

    void setVelocidade(float v);

private:
    float posicao;
    float velocidade;
    Direcao direcao;
};

#endif // CILINDRO_H