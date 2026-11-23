# Void Shooter

![Tela Principal do Jogo]
<img width="850" height="950" alt="Void Shooter" src="https://github.com/user-attachments/assets/4dd2e823-cc51-4fce-9bd0-478dd434ecf7" />



## Integrantes do Grupo
* Jonas Gonçalves de Lima
* RA:26032423

## Sobre o Jogo
**Void Shooter** é um jogo arcade de nave espacial desenvolvido em linguagem C utilizando a biblioteca Raylib. O objetivo é desviar e destruir meteoros que caem pelo espaço, gerindo a vida da nave e acumulando a maior pontuação possível.

## Tecnologias Utilizadas
* **Linguagem:** C
* **Biblioteca Gráfica e de Áudio:** Raylib[cite: 9]
* **Ambiente de Desenvolvimento:** Code::Blocks

## Instruções de Instalação e Controlos
### Como Jogar
* **Movimentação:** Teclas `W`, `A`, `S`, `D` ou Setas Direcionais.
* **Aceleração (Boost):** Manter pressionada a tecla `SHIFT` esquerdo ou direito.
* **Disparar:** Tecla `ESPAÇO`.
* **Iniciar Jogo:** Pressionar `ENTER` ou `ESPAÇO` no menu.
* **Voltar ao Menu:** Pressionar `M` na tela de Game Over.

### Execução
1. Vá até a aba **Releases** deste repositório e faça o download da versão empacotada[cite: 9].
2. Certifique-se de manter a estrutura de pastas (`Sprites`, `Sons`, `Fonte`) junto ao executável `.exe`.
3. Abra o jogo e divirta-se!

## Transparência de IA
Neste projeto, ferramentas de Inteligência Artificial foram utilizadas de forma colaborativa para auxiliar nas seguintes etapas:
* **Refatoração e Estruturação:** Auxílio na organização das máquinas de estados (Menu, Jogo, Game Over) e lógica do loop principal.
* **Tratamento de Colisões e Matemática:** Suporte na implementação das colisões circulares (`CheckCollisionCircles`) e restrições de limites da nave nas bordas da tela.
* **Balanceamento de Gameplay:** Discussão de ideias para calibrar a proporção de velocidade e cadência de surgimento dos meteoros.
