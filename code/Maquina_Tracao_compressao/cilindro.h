#ifndef CILINDRO_H
#define CILINDRO_H

class Cilindro
{
public:
    Cilindro();

    // Ações
    void avancar();
    void retornar();
    void parar();

    // Getters
    float getPosicao() const;
    float getVelocidade() const;

    // Setters
    void setVelocidade(float v);


private:
    float posicao;
    float velocidade;
    Direcao direcao;

};

#endif // CILINDRO_H