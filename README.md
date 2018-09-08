# Como fazer um clone da Box2D rodar no VS 2015 no Windows com GLFW

## Localização da solução

./Build/Box2D.sln

## Concept Doc

Idéia misturada de várias mecânicas a partir de:

* http://www.squidi.net/three/entry.php?id=1

* http://www.squidi.net/three/entry.php?id=2

* http://www.squidi.net/three/entry.php?id=3

* http://www.squidi.net/three/entry.php?id=24

* http://www.squidi.net/three/entry.php?id=34

* http://www.squidi.net/three/entry.php?id=44

* http://www.squidi.net/three/entry.php?id=52

* http://www.squidi.net/three/entry.php?id=56

* http://www.squidi.net/three/entry.php?id=67

* http://www.squidi.net/three/entry.php?id=68

* http://www.squidi.net/three/entry.php?id=74

* http://www.squidi.net/three/entry.php?id=77

* http://www.squidi.net/three/entry.php?id=85

* http://www.squidi.net/three/entry.php?id=86

* http://www.squidi.net/three/entry.php?id=106

* http://www.squidi.net/three/entry.php?id=114

* http://www.squidi.net/three/entry.php?id=122

* http://www.squidi.net/three/entry.php?id=123

* http://www.squidi.net/three/entry.php?id=128

* http://www.squidi.net/three/entry.php?id=185

* http://www.squidi.net/three/entry.php?id=187

* http://www.squidi.net/three/entry.php?id=198

* http://www.squidi.net/three/entry.php?id=211

* http://www.squidi.net/three/entry.php?id=222

* http://www.squidi.net/three/entry.php?id=242

* http://www.squidi.net/three/entry.php?id=254

### Características principais

Dois sistemas planetários orbitando suas estrelas

Cada jogador em um planeta de um sistema

Ambos começam no planeta mais próximo à estrela

Planetas e estrelas contêm massas e raios diversos, simétricos aos do o adversário

Jogador pode:

* construir foguetes
* construir torretas
* construir naves

Foguetes:

* demandam pedaço do planeta para seres contruídos
* tiram pedaço grande de um planeta que atingem
* têm propriedades diferentes

Torretas:

* demandam pedaço do planeta para seres contruídas
* lançam foguetes catapultados de tempos em tempos
* podem ser empilhadas
* têm propriedades diferentes

Naves:

* demandam pedaço do planeta para seres contruídas
* usadas para coletar pedaços de outro planeta do sistema do jogador
* usadas para fugir para outro planeta do sistema do jogador

Pedaço:

* tirar um pedaço de um planeta significa diminuir a massa e raio do planeta
* pedaço removido de planeta atingido por foguete é lançado na direção da normal ao centro do planeta
* pedaço sofre aceleração pela gravidade do sistema
* pedaço viajando no espaço que colide com planeta adiciona à massa e ao raio dele
* pedaço viajando no espaço que colide com a estrela adiciona à massa e ao raio dela
* estrela não perde pedaços

Condições de vitória:

* remover último pedaço do planeta do adversário sem ele ter nave
* remover último pedaço do último planeta do adversário

### Estilo

Estratégia RTS + sobrevivência

### Plataformas

PC multiplayer

### Arte conceitual

![Imagem dos sistemas](https://snag.gy/4jCsok.jpg)

tempo 0:

* 2 sistemas com:

	* 1 estrela

	* 4 planetas

	* 3 pedaços:

		* 1 vai pra estrela

		* 1 vai pra baixo mas talvez será puxado de volta eventualmente

		* 1 será absorvido pelo planeta

![Imagem dos sistemas](https://snag.gy/Dohwd8.jpg)

tempo1:

* 2 sistemas com:

	* 1 estrela

	* 4 planetas

	* 3 pedaços:

		* 1 está mais próxima ainda da estrela

		* 1 foi mais para baixo mas talvez será puxado de volta eventualmente

		* 1 já foi absorvido pelo planeta, então desapareu