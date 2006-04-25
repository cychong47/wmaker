


		       		GNU Window Maker
		       	       X11 Window Manager

	  	   	   <http://windowmaker.info>
		 	 <ftp://ftp.windowmaker.info>

				     por

		      	     Alfredo K. Kojima 

			 	 Dan Pascu

				    ]d


			       Web/FTP Master

			       Phillip Smith



		�Felicitaciones! Ha adquirido un dispositivo
	excelent�simo que le proporcionar� miles de a�os de uso sin
	problemas, si no fuera porque indudablemente lo destruir� a
	trav�s de alguna maniobra est�pida t�pica de consumidor. Por
	eso le pedimos por EL AMOR DE DIOS LEA ESTE MANUAL DEL
	PROPIETARIO CUIDADOSAMENTE ANTES DE DESEMPAQUETAR EL
	DISPOSITIVO. �YA LO DESEMPAQUET�, NO?  LO DESEMPAQUET� Y LO
	ENCHUF� Y LO ENCENDI� Y TOQUETE� LAS PERILLAS, Y AHORA SU
	CHICO, EL MISMO CHICO QUE UNA VEZ METI� UNA SALCHICHA EN SU
	VIDEOCASETERA Y ACCION� "AVANCE R�PIDO", ESTE CHICO
	TAMBI�N EST� TUOQUETEANDO LAS PERILLAS, �CIERTO? Y RECI�N
	AHORA EST� COMENZANDO A LEER LAS INSTRUCCIONES, ���CIERTO???
	NOSOTROS PODR�AMOS SIMPLEMENTE ROMPER ESTOS DISPOSITIVOS EN LA
	F�BRICA ANTES DE DESPACHARLOS, �SABE?
				-- Dave	Barry, "�Lea Esto Primero!"


Descripci�n
===========

Window Maker es el gestor de ventanas GNU para el Sistema de Ventanas X. Fue
dise�ado para emular la apariencia y funcionalidad de parte del GUI de NEXTSTEP(mr).
Procura ser relativamente r�pido y peque�o, rico en caracter�sticas, f�cil de configurar
y usar, con una simple y elegante apariencia sacada desde NEXTSTEP(mr).

Window Maker fue dise�ado teniendo en mente la integraci�n con GNUstep y por eso
es el gestor de ventanas "oficial". Es tambi�n parte del proyecto GNU (www.gnu.org)
. Lea mas sobre GNUstep m�s adelante en este archivo.


Pistas (informaci�n dada por las aplicaciones para integrarse bien con el gestor de
ventanas) para Motif(tm), OPEN LOOK(tm), KDE y GNOME tambi�n son soportados. 
Entonces puede reemplazar cualquiera de los gestores de ventana para estos entornos
con Window Maker manteniendo la mayor�a, si no todo, de la funcionalidad del
gestor de ventanas nativo.

Window Maker antes se llamaba WindowMaker.

Window Maker no tiene relaci�n con Windowmaker, el software para
hacer ventanas y puertas.


Documentaci�n
=============

Lea antes de preguntar.

* Los archivos README distribuidos por todas partes del �rbol de fuentes 
contienen informaci�n relacionada al contenido en los directorios. 

* INSTALL tiene instrucciones de instalaci�n y algunos consejos cuando tenga
alg�n problema. Significa que deber�a leerlo antes de la instalaci�n.
No fue escrito solo para ocupar espacio en el paquete...

* FAQ: Preguntas Frecuentes. LEALO!!! FAQ.I18N es para
preguntas relacionadas con la internacionalizaci�n.

* NEWS: lista los cambios visibles por el usuario desde la versi�n anterior. 
L�alo si est� actualizando.

* MIRRORS: algunos lugares alternativos donde puede obtener Window Maker, 
incluyendo paquetes de Window Maker espec�ficos para ciertas plataformas.

* BUGFORM: uselo para enviar reportes de errores. Por favor uselo.

* ChangeLog: �que cambi� desde la versi�n anterior?

* BUGS: lista de errores conocidos.

*** Tutorial

Hay un tutorial mantenido por Georges Tarbouriech en:

http://www.linuxfocus.org/~georges.t/

*** Gu�a del Usuario

La Gu�a del Usuario de Window Maker puede ser bajada desde el ftp oficial
o por sitios web.
Puede tambi�n ser vista en formato HTML en:

http://people.delphi.com/crc3419/WMUserGuide/index.htm

La Gu�a del Usuario explica como usar Window Maker, los archivos de configuraci�n 
y opciones.

*** man pages

Tipee "man wmaker" en el prompt del shell para obtener ayuda general sobre Window Maker.


Directorios y Archivos en el �rbol de Fuentes
=============================================

* Install es un script para configurar y compilar Window Maker de una forma
f�cil (no es que la forma normal sea dif�cil, pero...).

* AUTORES: los cr�ditos

* TODO: planes para el futuro.

* contrib/ tiene algunos parches aportados que no est�n soportados por Window Maker
  porque entran en conflicto con la filosof�a de dise�o de los desarrolladores o por
  alguna otra raz�n.

* util/ tiene varios programas utilitarios.

* WPrefs.app/ es el programa de configuraci�n.

* src/wconfig.h posee opciones de compilaci�n que puede cambiar para 
  seleccionar algunas opciones/caracteristicas y otras cosas.

* WINGs/ biblioteca widget para imitaci�n de NEXTSTEP.

* wrlib/ biblioteca de procesamiento de imagen.

* po/ posee cat�logos de mensajes  que son las versiones traducidas de los mensajes
mostrados por Window Maker.

* docklib-x.x.tar.gz es una biblioteca para escribir dockapps.

SOCORRO!!!
==========

Hay una lista de correo para discutir sobre Window Maker en
wm-user@windowmaker.info. Para suscribirse, envie un mensaje que contenga:

	subscribe
en el tema del mensaje a wm-user-request@windowmaker.info

Si tiene algun problema, pregunte aqu� (despu�s de leer los docs, por supuesto). Es
m�s probable que las personas de la lista sepan contestar sus preguntas
que nosotros. Para reportes de errores use el BUGFORM.

Si tiene un problema con una versi�n precompilada de Window Maker 
(rpm, deb etc), primero pregunte a la persona que hizo el paquete.

NOTA IMPORTANTE: cuando pida ayuda (en la lista de correo o a los desarrolladores,
directamente) *siempre* envie informaci�n sobre el sistema que est� usando. Puede
usar la secci�n de informaci�n del sistema al final del BUGFORM como una gu�a. 
Otra cosa: por favor no envie correo HTML.

Tambi�n hay un canal de IRC #windowmaker en openprojects. �nase aqu�, 
conecte su cliente de irc a irc.openprojects.net, irc.linux.com o alg�n otro
servidor de esa red.

GNUstep
=======

GNUStep es un completo sistema de desarrollo orientado a objetos, basado en la 
especificaci�n OpenStep liberada por NeXT(tm) (ahora Apple(tm) y Sun(tm)). Ello
proveer� todo lo que se necesita para producir aplicaciones multiplataforma, 
orientadas a objetos, gr�ficas (y no gr�ficas); suministrando dentro de otras cosas,
bibliotecas base del sistema, una estructura de alto nivel para aplicaciones GUI que
usan un modelo de imagenes de tipo Display PostScript(tm) (DGS), objetos para acceso
a bases de datos relacionales, objetos distribuidos y un entorno de desarrollo gr�fico,
con herramientas como un modelador de interfaces, un sistema para administraci�n del 
proyecto (central de proyecto) y otras herramientas.

El sistema de desarrollo de GNUStep ser� usado para crear un entorno de usuario,
con todo lo necesario para una completa interface gr�fica de usuario, tal como 
un visualizador de archivos, editores de texto y otras aplicaciones. Note que el
entorno de usuario (o "entorno de escritorio") es solo un peque�a parte de todo
el proyecto GNUStep y por lo tanto no "compite" con otros proyectos como KDE o GNOME,
simplemente porque son cosas completamente diferentes.

Para m�s informaci�n sobre el proyecto GNUStep, visite: http://www.gnustep.org y
http://gnustep.current.nu


Ejecutando multiples instancias de Window Maker
===============================================

No es una buena idea eejcutar m�s de una instancia de Window Maker desde
el mismo usuario (ya que wmaker usar� los mismos archivos de configuraci�n)
al mismo tiempo. Podr�a obtener un comportamiento inesperado cuando Window
Maker actualiza sus archivos de configuraci�n.

Si de verdad desea hacer esto, intente ejecutar Window Maker con la opci�n
de linea de comando --static ya que as� no actualizar� o cambiar� ninguno de los
archivos de configuraci�n.

Soporte para Sonido
===================

El sonido es soportado por los sistemas Linux y FreeBSD con el uso de 
un m�dulo distribuido separadamente llamado WSoundServer. Hay tambi�n 
una herramienta de configuracion gr�fica para definir sus sonidos llamada
WSoundPref.
Puede bajar esto en:
http://shadowmere.student.utwente.nl/

Note que debe compilar Window Maker con el par�metro --enable-sound
y definir la opci�n DisableSound a NO.


Ajuste de Rendimiento.
=====================
Si quiere disminuir el uso de memoria por parte de Window Maker y mejorar el 
rendimiento, manteniendo una linda apariencia y buena funcionalidad, siga los
items de abajo:

- use texturas s�lidas para todo, principalmente barras de t�tulo y men�es.
  Si quiere un escritorio de aspecto lindo, use el estilo Tradicional.
- Apague NewStyle y Superfluous
- No una muchos atajos al men� y mantenga solo los items esenciales en el men�.
- Active DisableClip
- edite wconfig.h y desactive el NUMLOCK_HACK y lo mismo con las caracter�sticas
  que no use (tenga en mente que algunos de los #defines podr�an no funcionar,
  ya que ellos no est�n completamente soportados). Aseg�rese de mantener siempre
  Numlock y ScrollLock apagados.
- Active DisableAnimations. Puede tambi�n #undefine ANIMATIONS en wconfig.h
- quite las entradas por defecto IconPath y PixmapPath para contener solo las
  rutas que en verdad tiene en su sistema.
- no use im�genes grandes en el fondo ra�z.
- quite el soporte para los formatos de imagen que no use.
- para reducir el uso de la memoria, desactive el cach� de �cono, definiendo 
  la variable de entorno RIMAGE_CACHE a 0. Si quiere aumentar el rendimiento 
  a expensas del uso de la memoria, defina este valor a un valor igual al 
  n�mero de �conos distintos que use.

Control del Mouse por Teclado
=============================

Muchas personas preguntan sobre agregar control por teclado al mouse, como
en fvwm, pero Window Maker no tendr� tal caracter�stica. La extensi�n XKB 
soporta simulaci�n de mouse desde el teclado, de una manera mucho m�s poderosa
que cualquier otra simulaci�n hecha por un administrador de ventanas.

Para activarlo, presione la combinaci�n de teclas Control+Shift+NumLock o 
Shift+NumLock. Debiera escuchar el beep del parlante. Para desactivarlo,
haga lo mismo.

Para controlar el mouse el teclado num�rico se usa as�:
- 4 (flecha izquierda), 7 (Home), 8 (flecha arriba), 9 (PgUP), 6 (flecha derecha),
  3 (PgDn), 2 (flecha abajo) y 1 (Fin) mueve el mouse a la correspondiente 
  direcci�n;
- sosteniendo una de las teclas de arriba y luego sosteniendo la tecla 5 mover�
el puntero m�s r�pido;
- / seleccionar� el primer bot�n del mouse (bot�n izquierdo);
- * seleccionar� el segundo bot�n del mouse (bot�n del medio);
- - seleccionar� el tercer bot�n del mouse (bot�n derecho);
- 5 har� un click con el bot�n actualmente seleccionado del mouse;
- + har� un doble click con el bot�n actualmente seleccionado;
- 0 (Ins) cliquear� y mantendr� el bot�n seleccionado actualmente;
- . (Del) liberar� el bot�n seleccionado actualmente que fue anteriormente
  cliqueado con la tecla 0 (Ins).

Los valores anteriores de las teclas funcionar�n en un servidor X XFree86 3.2
(X11R6.1) pero su alcance puede variar.

Como hacer un gdb backtrace
===========================

Backtraces pueden ayudarnos a arreglar errores que hicieron que Window Maker falle.
Si encuentra un bug que hace fallar a Window Maker, por favor envie un backtrace con su
reporte de error.

Para hacer un backtrace �til, necesita un archivo core con informaci�n de depuraci�n
producida por Window Maker cuando fall�. Deber�a haber sido instalado sin stripping tambi�n.

Para compilar wmaker con informaci�n de depuraci�n:

./configure
make CFLAGS=-g

Si obtiene el cuadro de di�logo que le dice que wmaker fall� y le 
pregunta que hacer, resp�ndale "Abortar y dejar un archivo core"

script
cd src
gdb .libs/wmaker path_to_the_core_file

Luego, en el prompt gdb escriba "bt". Salga de gdb escribiendo "quit"
y luego, en el prompt del shell, scriba "exit"

El archivo llamado typescript contendr� el backtrace.

Derechos de Autor y Descargo de Responsabilidad
===============================================

Window Maker est� registrado por Alfredo K. Kojima y est� licensiado por la 
Licensia P�blica General GNU. Lea el archivo COPYING para leer la licensia
completa.

Los �conos que son distribuidos con este programa y fueron hechos por Marco
van Hylckama Vlieg, est�n licenciados por la Licencia P�blica General GNU. 
Lea el archivo COPYING para leer la licencia completa.

Los �conos listados en COPYING.WTFPL y son distribuidos en este programa
fueron hechos por Banlu Kemiyatorn (]d), est�n licenciados por la 
"do What The Fuck you want to Public License". Lea el archivo COPYING.WTFPL
para leer la licencia completa.

NeXT, OpenStep y NEXTSTEP son marcas registradas de NeXT Computer, Inc.
Todas las otras marcas registradas son propiedad de sus respectivos due�os.

Los autores se reservan el derecho de hacer cambios en el software sin previo
aviso.

Autores
=======

Alfredo K. Kojima <kojima@windowmaker.info>
Dan Pascu <dan@windowmaker.info>
]d <id@windowmaker.info>

Por favor no nos haga preguntas antes de leer la documentaci�n (especialmente 
la FAQ, este archivo y los archivos INSTALL) y sobre cosas "cool" que ve en
las capturas de pantalla del escritorio de las personas.

El archivo AUTHORS contiene una lista de las personas que han contribuido 
con el proyecto. El nombre de las personas que han ayudado con localization 
(traducci�n) se puede encontrar en po/README y Window Maker/README

Si tiene alg�n comentario, arreglos y reportes de errores (complete BUGFORMs)
y envi�melos a developers@windowmaker.info



traducido por Efra�n Maximiliano Palermo <max_drake2001@yahoo.com.ar>
