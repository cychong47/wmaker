
			Instrucciones de Instalaci�n para Window Maker



PLATAFORMAS SOPORTADAS
======================
(obs: Alguien me mencion� que lo compil� en...)

- Intel GNU/Linux Conectiva 5.9 (beta)
- Intel GNU/Linux Slackware
- Intel GNU/Linux Debian
- Intel GNU/Linux other distributions
- Sparc GNU/Linux RedHat 5.1
- PowerPC GNU/MkLinux
- Alpha GNU/Linux RedHat 5.1
- FreeBSD
- NetBSD
- OpenBSD
- BSDI 4.0
- Solaris 2.5.1, 2.5.2
- Solaris 2.6.0
- Solaris 2.7beta
- SCO Unix
- SGI Irix 5.x, 6.5
- OSF/1
- HP-UX
- AIX 3.2.5
- AIX 4.1.4 / IBM PowerPC
- AIX 4.3.1 / IBM CC compiler
- AIX 4.3.2 / IBM PowerPC
- AIX 5.3
- DEC Alpha/Digital UNIX 4.x
- XFree86 / OS/2
- Corel NetWinder
- SunOS 4.x
- PowerMac / Power MachTen 4.1.1 over MacOS
- Amiga 3000 running RedHat Linux 5.1 (Rawhide)
- IBM S/390 running Linux
- iBook running Darwin
- Windows NT with Cygwin/XFree86
- Sony PlayStation2 running Linux

Todas las marcas registradas est�n registradas por sus due�os. (duh)

Los parches que lo hagan funcionar en otras plataformas son bienvenidos.


REQUERIMIENTOS:
==============

El siguiente software se necesita para usar Window Maker:

- X11R6.x	
	Window Maker puede ser compilado en versiones m�s antiguas de X, 
	como X11R5 (Solaris) o X11R4 (OpenWindows) pero no funcionar� 100%
	correctamente.
	En tales servidores no habr� �conos de aplicaci�n y tendr� problemas
	usando el dock. Actualizar las bibliotecas cliente (Xlib, Xt, etc) 
	ayudar� si no puede actualizar el servidor.

Lo siguiente se necesita para compilar Window Maker:

- Requerimientos b�sicos y obvios
	Si compila Window Maker, aseg�rese de tener gcc (u alg�n otro
	compilador ANSI C) y los archivos header de X instalados. Especialmente
	para los usuarios de Linux principiantes: debe instalar todos los paquetes
	de desarrollo de X y la suite gcc. De lo contrario no ser� capaz de 
	compilar ning�n programa X, incluyendo Window Maker.

- libPropList
	Esta biblioteca se puede encontrar en ftp://ftp.windowmaker.org/pub/libs
	o en ftp://ftp.gnome.org/pub/libPropList
	Inst�lela antes de compilar Window Maker.

- autoconf, automake y libtool
	Estas herramientas NO son necesarias, pero SI tiene una o m�s de ellas
	instaladas, aseg�rese de tener TODO lo siguiente con estas versiones
	 exactas:
	 	
		autoconf 2.13
		automake 1.4
		libtool 1.3
	
	Si tiene una versi�n distinta, desact�velas temporalemte renombr�ndolas
	a otras cosa o desinstal�ndolas desde su sistema. Si no desarrolla
	 software no las necesita, as� que puede desinstalarla sin peligro.

- lex (o flex) y yacc (o bison)
	Estas son usadas por libPropList. lex en realidad no se necesita ya que
	su archivo de salida est� incluido, pero o yo o automake es tonto,
	causando que el script configure para libPropList simplemente 
	aborte sin ning�n motivo si lex no es encontrado.

OPCIONAL:
=========
Estas bibliotecas no son necesarias para hacer que Window Maker funcione,
 pero est�n soportadas en caso de que quiera usarlas. Los n�meros de versi�n
 son aquellos que yo tengo (y por lo tanto, garantizo que funciona), pero 
 otras versiones podr�a funcionar tambi�n.

- libXPM 4.7 o m�s actual.
	Versiones antiguas pueden no funcionar!!!
	Disponible en ftp://sunsite.unc.edu/pub/Linux/libs/X/

	Hay soporte nativo para archivos XPM, pero no cargar� imagenes de
	algunos formatos poco comunes.
	
-libpng 0.96 o m�s actual y zlib
	Para soporte de im�genes PNG.
	http://www.cdrom.com/pub/png/

- libtiff 3.4 o m�s actual.
	Para soporte de imaen TIFF.
	Puede obtenerla en ftp://ftp.sgi.com/graphics/tiff

- libjpeg 6.0.1 o m�s actual
	Para soporte de imagen JPEG
	http://www.ijg.org/

- libgif 2.2 o libungif
	Para soporte de imagen GIF.
	ftp://prtr-13.ucsc.edu/pub/libungif/

- libHermes 1.3.2 o m�s actual
	Para conversi�n a pixel m�s r�pida en la biblioteca wraster.
	(se usa solo en algunas conversiones - para visuales Color Verdadero)
	http://www.clanlib.org/hermes/

- GNU xgettext
	Si quiere usar mensajes traducidos, necesitar� GNU gettext.
	Otras versiones de gettext no son compatibles y no funcionar�n.
	Obtenga la versi�n GNU desde ftp://ftp.gnu.org

OPCIONES DE CONFIGURACI�N:
=========================
Estas opciones pueden ser pasadas al script configure para activar/desactivar
algunas opciones de Window Maker. Ejemplo:

./configure --enable-kde --enable-gnome

configurar� Window Maker para que sea compilado con soporte para KDE y GNOME.

Para obtener una lista de otras opciones, ejecute ./configure --help

--with-libs-from
	especifica rutas adicionales por donde se debe buscar bibliotecas.
	El -L flag debe preceder a cada ruta, tal como:
	
	--with-libs-from="-L/opt/libs -L/usr/local/lib"

--with-incs-from
	especifica rutas adicionales para la b�squeda de archivos header.	
	El par�metro -I debe preceder a cada ruta, tal como:
	
	--with-incs-from="-I/opt/headers -I/usr/local/include"

--enable-single-icon
	activa el agrupamiento de todos los appicons (iconos de aplicaciones)
	del WM_CLASS+WM_INSTANCE en uno solo. Esta caracter�stica no es soportada
	por todos los desarrolladores. Si tiene alg�n problema con ella, contacte
	a su autor:	Christopher Seawood <cls@seawood.org>

--disable-shm
	desactiva el uso de la extensi�n MIT de memoria compartida. Esto 
	ralentizar� la generaci�n de texturas un poco, pero en algunos casos 
	parecer� necesario debido a un error que se manifiesta como �conos y
	texturas desordenadas.

--disable-motif 
	desactiva el soporte para el gestor de ventanas mwm.

--enable-openlook
	activa el soporte para el gestor de ventanas OPEN LOOK(tm)

--enable-gnome
	activa el soporte para el gestor de ventanas GNOME.

--enable-kde
	activa el soporte para el gestor de ventanas kde/kwm.

--enable-lite
	quita cosas que ya est�n soportadas en los entornos de escritorio, 
	tal como KDE y Gnome. Desactiva cosas como: lista de ventanas, 
	men� de aplicaciones ra�z, selecci�n de ventanas m�ltiple. Note 
	que no podr� salir m�s desde dentro de Window Maker; tendr� que usar 
	kill con la se�al SIGTERM o salir de KDE. No aconsejo activarlo.

--enable-modelock
	Soporte para bloqueo de estado de lenguaje XKB. Si no sabe que es esto
	probablemente no lo necesite.

--enable-sound	
	activa el soporte del m�dulo para efectos sonoros.

--disable-xpm   
	desactiva el uso de la biblioteca XPM aunque este disponible en su
	 sistema.

--disable-png	
	desactiva el uso de la biblioteca PNG.

--disable-tiff
	desactiva el uso de la biblioteca TIFF.

--disable-gif
	desactiva el uso de la biblioteca GIF.

--disable-jpeg
	desactiva el uso de la biblioteca JPEG.

--disable-shape
	desactiva la forma de ventanas (para oclock, xeyes etc.)

NOTAS ESPEC�FICAS A LA PLATAFORMA:
=================================

- m�quinas DEC/Alpha

#>>>>>>>>>>>
From: Anton Ivanov <aivanov@eu.level3.net>
To: Marcelo E. Magallon <mmagallo@debian.org>
Subject: Re: El paquete WindowMaker funciona bien en Alpha?

> Hola,
> 
>  Estuve leyendo algunos documentos en el tarball de WindowMaker,
>  y encontr� esto:
> 
>  | - m�quinas DEC/Alpha
>  |         podr�a necesitar pasar el par�metro --disable-shm a configure,
>  |         as� ./configure --disable-shm
> 
>  alguien est� teniendo problemas con WindowMaker en Alpha?  Puede alguien
>  por favor probar esto?  Deber�a el par�metro ser pasado al compilar 
>  en Alpha?

Descargo de responsabilidad: alphas bajo mi mando nunca han ejecutado X y are
least likely to suddenly start running it anytime soon.

	Alpha suele tener alguna rid�cula poca cantidad de memoria compartida
configurada.

As� que much�simas aplicaciones suelen to barf. Concretamente - cdrecord, mysql server, etc.
	
	Verifique donde est� el suyo en este momento y s�balo a un valor m�s adecuado catting la entrada
	adecuada de /proc o cambiando el /usr/src/linux/include/asm/shmparam.h.

	De lo contrario la memoria compartida en alpha debiera ser completamente funcional y no veo raz�n
para desactivarla. Las m�as est�n aumentadas a 32 o m�s en muchas m�quinas.
	
	Y si recuerdo correctamente los comentarios en aqu�l archivo est�n en realidad mal.
	El valor no est� en bytes, pero si en palabra de tama�o m�quina. Para alpha *8.
	
	Como dije - no ejecuto X en ellas asi que apliqu� a todas #include "stdisclaimer.h".
#<<<<<<<<<<<<

- SCO Unix - ejecute configure as�
	CFLAGS="-belf -DANSICPP" ./configure 

-SunOS, Solaris
	Si tiene gcc instalado, ejecute configure como:
	CPP_PATH="gcc -E -x c" ./configure
	Sun cpp le falta algunas caracter�sticas que necesita Window Maker y
	 puede causarle problemas al analizar sintacticamente los archivos config.
	 Tambi�n podr�a necesitar usar el --with-libs-from y --with-incs-from para
	 suministrarle el directorio donde libtiff se aloja.
	Alguien me envi� un mensaje dici�ndome que tambi�n debe hacer que /usr/local/lib 
	sea la primera ruta en LD_LIBRARY_PATH para que funcione.
	
	Si tiene un Ultra Creator 3D o alguna otra m�quina con gr�ficos high-end,
	aseg�rese de iniciar el servidor X con el valor visual por defecto a 24bpp o
	 podr�a experimentar problemas con colores destrozados.
	 Este es un error de wmaker y ser� reparado.
	
- GNU/Linux en general
	Aseg�rese de tener /usr/local/lib en /etc/ld.so.conf y de ejecutar 
	ldconfig despu�s de instalar.
	Desinstale cualquier versi�n empaquetada de Window Maker antes de 
	instalar una nueva versi�n.
	
- RedHat GNU/Linux
	Los sistemas RedHat tienen varios problemas molestos. Si lo usa,
	aseg�rese de seguir los pasos de m�s abajo o Window Maker no funcionar�:

	* si instal� el Window Maker que viene con RedHat, desinst�lelo antes de
	actualizar;
	
	*aseg�rese que no tiene las variables de entorno LANG y LINGUAS establecidas a
	 en_RN;
	
	*aseg�rese de tener /usr/local/bin en su variable de entorno PATH;

	* aseg�rese de tener /usr/local/lib en /etc/ld.so.conf antes de ejecutar 
	ldconfig;
	
	*si tiene problemas que mencionan un menaje de error con --no-reexec 
	desinstale libtool-1.2b e instale libtool-1.3 en su lugar. libtool-1.3 
	se puede encontrar en ftp.gnu.org. Tambi�n lea la secci�n TROUBLESHOOTING
	 (PROBLEMAS);
	
	* si instal� el paquete Window Maker desde RedHat y est� instalando una
	nueva versi�n de WM a mano (compilandolo usted mismo), desinstale antes el 
	paquete desde RedHat.
	 
	*aseg�rese de tener un enlace simb�lico desde /usr/include/X11 hacia 
	/usr/X11R6/include/X11 (si no, tipee ln -s /usr/X11R6/include/X11 /usr/include/X11)
	
	* aseg�rese de tener /lib/cpp apuntando al programa cpp.
	
	Si tiene alguna duda en cuanto a hacer algunas de las cosas de arriba, 
	por favor no dude en contactar el soporte para usuarios de RedHat. Ellos
	 responder�n amablemente a todas sus preguntas en lo que respecta a su sistema.
	 Ellos tambi�n conocen mucho m�s acerca de su propio sistema que nosotros 
	 (nosotros no usamos RedHat).
	
- PowerPC MkLinux
	Necesitar� tener la �ltima version de Xpmac. Las versiones m�s antiguas
	parecen tener errores que producen el cuelgue del sistema.
	
- Debian GNU/Linux
	Si quiere soporte JPEG y TIFF, aseg�rese de tener libtiff-dev y
	 libjpeg-dev instalados.

- SuSE GNU/Linux
	Si instal� el paquete Window Maker desde SuSE, 
	desinst�lelo antes de instentar compilar wmaker o podr�a
	tener problemas.
	

- MetroX (version desconocida)
	MetroX tiene un error que corrompe pixmaps que se establecen como 
	fondos de ventana. Si usa MetroX y tuvo problemas raros con texturas, no use 
	texturas en las barras de t�tulos. O use un servidor X distinto.

INSTALACI�N:
=============

Compilando Window Maker
------------------
	Para un comienzo r�pido, tipee lo siguiente en el prompt del shell:

	./configure
	make

luego, reg�strese como root y tipee:

	make install
	ldconfig

o si quiere remover los s�mbolos de depuraci�n desde los binarios y hacerlos m�s
 peque�os, puede tipear:

	make install-strip
	ldconfig

Esto compilar� e instalar� Window Maker con los par�metros por defecto.

Si quiere personalizar algunas opciones de compilaci�n, puede hacer lo siguiente.
	
	1. (opcional)Mire en la secci�n OPCIONES DE CONFIGURACI�N para ver las
	 opciones disponibles. Tambi�n ejecute:
 
	./configure --help
	
	para obtener un listado completo de otras opciones que est�n disponibles.

	2. Ejecute configure con las opciones que quiera. Por ejemplo, si quiere 
	usar la opci�n --enable-kde, tipee:
	
	./configure --enable-kde
	
	3. (opcional) Edite src/wconfig.h con su editor de texto favorito y
	 echele un vistazo por algunas opciones que podr�a querer cambiar.
	 
	4. Compile. Solo tipee:

	make
	
	5. Reg�strese como root (si no puede hacerlo, lea la secci�n "No tengo la contrase�a de root" :-()
	 e instale Window Maker en su sistema:
		su root
		make install


Configuraci�n espec�fica del usuario
------------------------------------

Estas instrucciones no necesitan ser seguidas al actualizar Window Maker 
desde una versi�n m�s antigua, a menos que se indique de otra forma en el archivo
 NEWS.

Todo usuario en su sistema que desee ejecutar Window Maker debe hacer lo siguiente:

	1. Instale los archivos de configuraci�n de Window Maker en su directorio home.
Tipee:
	wmaker.inst

	wmaker.inst instalar� los archivos de configuraci�n de Window Maker y
configurar� X para que autom�ticamente lance Window Maker al inicio.

	Eso es todo!
	
	Puede tipear "man wmaker" para obtener algo de ayuda general para la 
configuraci�n y otras cosas.
Lea la Guia de Usuario para una explicaci�n m�s a fondo de Window Maker.

Podr�a querer dar una mirada a la FAQ tambi�n.

Instalando el paquete extras
----------------------------

Desempaquete WindowMaker-extra-<n�mero-de-versi�n>.tar.gz en /usr/local/share

Puede obtener el archivo en ftp://ftp.windowmmaker.org. Este archivo es optativo
 y solo tiene unos pocos �conos, y temas. Busque el �ltimo <n�mero-de-versi�n> 
 disponible.
 Tambi�n hay un WindowMaker-extra.readme que le ense�a donde ver�a ir ese paquete.


No tengo la contrase�a de root :(
--------------------------------

Si no puede obtener privilegios de superusuario (no puede ser root) puede 
instalar wmaker en su propio directorio home. Para esto, proporcione la 
opci�n --prefix al ejecutar configure en el paso 2 de compilando Window Maker. 
Tambi�n necesitar� proporcionar la opci�n --with-appspath, para especificar la ruta
para WPrefs.app. Ejemplo:

./configure --prefix=/home/jshmoe --with-appspath=/home/jshmoe/GNUstep/Apps

Luego haga /home/jshmoe/bin para que se lo incluya en su ruta de b�squeda, agregue
/home/jshmoe/lib a su variable de entorno LD_LIBRARY_PATH y ejecute bin/wmaker.inst

Por supuesto, /home/jshmoe se supone que va a ser reemplazado con la ruta a su 
directorio home real.


ACTUALIZANDO
============
Si est� actualizando desde una versi�n antigua de Window Maker:

	1. Configure y compile Window Maker como siempre.
	2. Instale Window Maker (pero no ejecute wmaker.inst)
	3. Lea el archivo NEWS y actualice sus archivos de configuraci�n, 
	   si es necesario.

PROBLEMAS
=========

Cuando tenga alguno problemas durante la configuraci�n (al ejecutar configure),
tal como no poder usar una biblioteca de formato gr�fico que piensa tener instalada,
mire en el archivo config.log para obtener ideas sobre el problema.

== Error al cargar las fuentes, siempre que existan.

Intente recompilar sin el soporte NLS.

== Error al configurar

ltconfig: unrecognized option `--no-reexec'
Try `ltconfig --help' for more information.
configure: error: libtool configure failed

quite la opci�n --no-reexec desde aclocal.m4 y libPropList/aclocal.m4 y
 reconfigure.
Tambi�n aseg�rese que las versiones de autoconf y automake que tenga instaladas son:

autoconf 2.13
automake 1.4
libtool 1.3

Note que ella no debe ser libtool 1.2b, debe ser libtool 1.3, 
desde los sitios GNU.

== No puedo encontrar proplist.h o libPropList.something

Baje e instale libPropList desde los lugares ya citados en alg�n lugar 
de este archivo.

== configure no detecta libtiff, u otras bibliotecas gr�ficas.

Elimine config.cache, luego vuelva a ejecutar configure a�adiendo las siguientes
 opciones a configure (entre sus otras opciones):

--with-libs-from="-L/usr/local/lib"
--with-incs-from="-I/usr/local/include -I/usr/local/include/tiff"

Sustituya las rutas donde est�n localizadas sus bibliotecas gr�ficas y sus 
correspondientes archivos header. Puede colocar rutas m�ltiples en cualquiera de 
estas opciones, como se muestra en el ejemplo de --with-incs-from . Solo coloque
un espacio entre ellas.

== configure no detecta libXpm. 

* Verifique si tiene un enlace simb�lico desde libXpm.so.4.9 a libXpm.so

== Segmentation fault al inicio.

* Verifique si la versi�n de libXPM que tiene es por lo menos la 4.7

* Verifique si tiene una versi�n actualizada de ~/GNUstep/Defaults/WindowMaker

Si no est� seguro, intente renombrar ~/GNUstep a ~/GNUtmp y luego ejecute wmaker.inst

== "...: your machine is misconfigured. gethostname() returned (none)"

* el hostname de su m�quina est� definido a algo inv�lido, como comenzar con
	un par�ntesis. Haga un man hostname para obtener informaci�n acerca de como definirlo.


== El men� ra�z contiene solo 2 entradas. ("XTerm" y "Exit...")

* Window Maker no est� encontrando cpp (el preprocesador de C). Si su 
cpp no est� ubicado en /lib/cpp, edite src/config.h y corrija la ruta en 
CPP_PATH.

== checking lex output file root... configure: error: cannot find output from true; giving up

* Lea la secci�n REQUERIMIENTOS de este archivo.


LOCALES/INTERNACIONALIZACI�N
============================

Window Maker tiene soporte de idioma nacional. Para activar este soporte, 
debe compilar Window Maker con algunos par�metros adicionales.

0 - Debe tener el paquete GNU gettext instalado. Puede obtenerse en
ftp://prep.ai.mit.edu/pub/gnu/gettext-nnn.tar.gz

Los pasos 1 al 3 pueden saltearse si usa el script Install.

1 - Debe seleccionar los idiomas que quiere soportar. Defina el
LINGUAS a la lista de locales que quiera. El Ingl�s siempre est�
soportado. Ejemplo:

setenv LINGUAS "pt ja de"
en csh

o

export LINGUAS;LINGUAS="pt ja de"
en sh

La lista de locales soportados se pueden encontrar en po/README.
El Ingl�s es el idioma pr defecto.

Lea po/README si desea traducir y mantener archivos locale para otros 
idiomas.

2 - Adicionalmente, si su idioma usa caracteres multi-byte, tal como
Japon�s o Coreano, debe definir la opci�n MultiByteText a YES
en ~/GNUstep/Defaults/WMGLOBAL

3 - Configure, compile e instale Window Maker normalmente.

4 - Para seleccionar un locale particular en tiempo de ejecuci�n debe definir la
 variable de entorno LANG al locale que quiera. Por ejemplo, si quiere definir
el locale portugu�s, debe ejecutar

setenv LANG pt

en csh o

export LANG; LANG=pt

en Bourne sh y similares

Nota: Si tiene definida la variable de entorno LC_CTYPE, debe
indefinirla antes de ejecutar wmaker.

Window Maker busca los archivos de definici�n de men� en el siguiente orden:
(para portugu�s brasile�o, en este caso):

menu.pt_BR
menu.pt
menu

5 - Si elige un idioma que usa caracteres multi-byte, debe configurar 
las fuentes adecuadamente. Lea la p�gina del manual para XCreateFontSet 
para obtener m�s detalles sobre esto. Debe cambiar el archivo ~/G/D/Windowmaker
para las fuentes usadas en barras de t�tulo, men�s y otras cosas. Para las fuentes
usadas en ventanas de di�logo, cambie ~/G/D/WMGLOBAL. El %d en los nombres de las
fuentes no debe ser quitado. Puede tambi�n usar el script wsetfont proporcionado para
esta tarea. Lea el mismo script para obtener instrucciones.

Por ejemplo, puede especificar lo siguiente en ~/G/D/WindowMaker:

WindowTitleFont = "-*-helvetica-bold-r-normal-*-12-*,-*-*-medium-r-normal-*-14-*";
MenuTitleFont = "-*-helvetica-bold-r-normal-*-12-*,-*-*-medium-r-normal-*-14-*";
MenuTextFont = "-*-helvetica-medium-r-normal-*-12-*,-*-*-medium-r-normal-*-14-*";
IconTitleFont = "-*-helvetica-medium-r-normal-*-8-*,-*-*-medium-r-normal-*-12-*";
ClipTitleFont = "-*-helvetica-bold-r-normal-*-10-*,-*-*-medium-r-normal-*-12-*";
DisplayFont = "-*-helvetica-medium-r-normal-*-12-*,-*-*-medium-r-normal-*-12-*";

y en ~/G/D/WMGLOBAL:

SystemFont = "-*-*-medium-r-normal-*-%d-*-*-*-*-*-*-*";
BoldSystemFont = "-*-*-medium-r-normal-*-%d-*-*-*-*-*-*-*";

Las 2 fuentes de arriba son usadas �nicamente por aplicaciones que usan WINGs
(WindowMaker y WPrefs.app)

El script wsetfont que se proporciona le permitir� cambiar las definiciones de fuentes
 de una manera f�cil. De una mirada al script para detalles de uso.

traducido por Efra�n Maximiliano Palermo <max_drake2001@yahoo.com.ar>
