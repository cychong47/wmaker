        Instrukce pro instalaci okenn�ho mana�era Window Maker

PODPOROVAN� PLATFORMY
=====================
("Podporovan�" znamen�, �e u� to na dan� platform� n�kdo zprovoznil...)

- Intel GNU/Linux Conectiva 5.9 (beta)
- Intel GNU/Linux Slackware
- Intel GNU/Linux Debian
- Intel GNU/Linux ostatn� distribuce
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
- IBM S/390 s Linuxem
- iBook s OS Darwin

Patche pro rozb�h�n� na jin�ch platform�ch jsou v�tan�.

PO�ADAVKY
=========

N�sleduj�c� software je pot�ebn�/nezbytn� pro b�h Window Makeru:

- X11R6.x
        Window Maker m��e b�t zkompilov�n na star��ch verz�ch X, jako
        je X11R5 (Solaris) nebo X11R4 (OpenWindows), ale nebude to pracovat
        100% spolehliv�. Na t�chto syst�mech nebudou fungovat ikony
        aplikac� a budete m�t probl�my s pou��v�n�m doku. Upgrade
        u�ivatelsk�ch knihoven (Xlib, Xt atd.) zlep�� tyto probl�my pokud
        nem��ete aktualizovat v� X server.

N�sleduj�c� software je pot�ebn� ke zkompilov�n� Window Makeru:

- Z�kl�dn� b�n� v�ci
        Kdy� budete komplivat Window Maker, tak se ujist�te, �e m�te gcc
        (nebo jin� ANCI C kompil�tor) a nainstalovan� hlavi�kov� soubory
        pro X. Hlavn� pro za��te�n�ky v Linuxu: mus�te nainstalovat v�echny
        X-devel bal�ky a gcc. Jinak nebudete schopni zkompilovat ��dn�
        program s grafick�m rozhran�m, tedy ani Window Maker.

- autoconf, automake a libtool
        Tyto n�stroje NEJSOU POT�EBA, ale kdy� m�te jeden nebo dva nebo
        v�echny t�i nainstalovan�, tak se UJIST�TE, �e m�te p�esn�
        n�sleduj�c� VERZE:
                autoconf 2.54
                automake 1.4
                libtool 1.4.2
        M�te-li odli�nou verzi, tak ji do�asn� p�ejmenujte, nebo ji rovnou
        odinstalujte z va�eho syst�mu. Pokud nebudete programovat, tak ji
        stejn� nebudete pot�ebovat, tak�e ji m��ete bezpe�n� odinstalovat.

Pozn. libProblist u� nen� pot�eba ke zkompilov�n� Window Makeru, proto�e
        libProblist byl p��mo zabudov�n do WINGs. Z toho d�vodu u� nen�
        pot�eba ani lex (flex) a yacc (nebo bison).


NEPOVINN�
=========

Tyto knihovny nejsou nutn� pro b�h Windo Makeru, ale jsou podporovan�, kdy�
je budete cht�t pou��t. Tyto verze jsou pou��van� v�vojov�m t�mem, kter�
garantuje, �e budou fungovat. Ostatn� verze by m�li fungovat tak�.

- libXPM 4.7 nebo nov�j��
        Star�� verze nemus� fungovat!!!
        Dostupn� na ftp://sunsite.unc.edu/pub/Linux/libs/X/

        Je zde zabudovan� podpora pro soubory XPM, ale nena�te obr�zky s
        nestandardn�m form�tem k�dov�n�.

- libpng 0.96 nebo nov�j�� a zlib
        Pro podporu PNG obr�zk�
        http://www.cdrom.com/pub/png/

- libtiff 3.4 nebo nov�j��
        Pro podporu TIFF obr�zk�
        Dostupn� na ftp://ftp.sgi.com/graphics/tiff

- libjpeg 6.0.1 nebo nov�j��
        Pro podporu JPEG obr�zk�
        http://www.ijg.org/

- libgif 2.2 nebo libungif
        Pro podporu GIF obr�zk�
        Dostupn� na ftp://prtr-13.ucsc.edu/pub/libungif/

-GNU xgettxt
        Kdy� chcete pou��vat �e�tinu nebo jin� jazyky krom� angli�tiny,
        tak pot�ebujete GNU xgettext.
        Ostatn� verze nejsou kompatibiln� a nebudou fungovat
        GNU verze je dostupn� na ftp://ftp.gnu.org


KONFIGURA�N� NASTAVEN�
======================

Tyto volby mohou b�t p�edan� konfigura�n�mu skriptu jako argumenty za
��elem povolen�/zak�z�n� ur�it� vlastnosti Window Makera.

P��klad:

./configura --enable-kde --enable-gnome

nakonfiguruje Window Maker s podporou KDE a GNOME

Seznam ostatn�ch mo�nost� dostanete spu�t�n�m ./configure --help

--with-libs-from
        specifikuje, kter� dal�� adres��e s knihovnami se maj� 
        prohled�vat. �et�zec -L mus� p�edch�zet ka�d�mu adres��i,
        nap�:
        --with-libs-from="-L/opt/libs -L/usr/local/lib"

--with-incs-from
        ur�uje, kter� dal�� adres��e s hlavi�kov�mi soubory se maj�
        prohledat. �et�zec -I mus� p�edch�zet ka�d�mu adres��i,
        nap�:
        --with-incs-from="-I/opt/headers -I/usr/local/include"

--enable-single-icon
        umo��uje skr�t v�echny ikony aplikac� WM_CLASS+WM_INSTANCE
        do jedn� jedin�. Tato vlastnost nen� podporovan� ze strany v�voj���.
        Kdy� budete m�t s touto funkc� probl�my, tak se obra�te na jej�ho
        autora: Christopher Seawood <cls@seawood.org>

--disable-shm
        zak�e pou��v�n� zd�len� pam�ti MIT. To trochu zpomal� generov�n�
        textur, ale v n�kter�ch p��padech se to jev� jako nezbytnost z d�vodu
        chyby, kter� zp�sobuje �patn� zobrazov�n� ikon a textur.

--disable-motif
        zak�e podporu pokyn� pro okenn� mana�er mwm.

--enable-lite
        odstran� n�stroje a funkce, kter� jsou u� dostupn� v desktopov�ch
        pros�ed�ch KDE a GNOME. Odstran� se: seznam oken, menu aplikac�,
        v�b�r v�ce oken. Uv�domte si, �e takto u� nebudete schopni ukon�it
        samotn� Window Maker pomoc� aplika�n�ho menu. Budete muset zab�t Window
        Maker z textov� konzole nebo ho ukon�it z KDE nebo GNOME.
        Nedoporu�uje se povolit tuto vlastnost.

--enable-modelock
        podpora pro XKB nastaven� jazyka. Kdy� nev�te, o co jde, tak to
        pravd�podobn� nebudete pot�ebovat.

--enable-sound
        povol� podporu modulu zvukov�ch efekt�.

--disable-xpm
        zak�e podporu knihovny XPM, pokud je dostupn� na va�em syst�mu.

--disable-png
        zak�e podporu knihovny PNG.

--disable-tiff
        zak�e podporu knihovny TIFF.

--disable-gif
        zak�e podporu knihovny GIF.

--disable-jpeg
        zak�e podporu knihovny JPEG.

--disable-shape
        zak�e tvarovan� okna (pro oclock, xeyes, atd.).

PO�ADAVKY PRO SPECIFICK� PLATFORMY
==================================

-DEC/Alpha

        N�sleduj�c� mail nen� p�elo�en, ale hovo�� se v n�m, �e pravd�podobn�
        nen� pot�eba konfigurovat Window Maker na Alph� s volbou --disable-shm.

-------------------------------------------------------------------------------
        From: Anton Ivanov <aivanov@eu.level3.net>
        To: Marcelo E. Magallon <mmagallo@debian.org>
        Subject: Re: Is the WindowMaker package working ok on Alpha?

> Hi,
> 
>  I was reading some docs on the WindowMaker tarball, and found this:
> 
>  | - DEC/Alpha machines
>  |         You might need to pass the --disable-shm flag to configure,
>  |         like ./configure --disable-shm
> 
>  is anyone having problems with WindowMaker on Alpha?  Can someone
>  please test this?  Should the flag be passed when building on Alpha?

Disclaimer: alphas under my command have never run X and are least likely to 
suddenly start running it anytime soon.

        Alpha used to have some ridiculously low amount of shared memory
configured. 
So quite a lot of apps used to barf. Namely - cdrecord, mysql server, etc.

        Check where is yours at the moment and raise it to a more appropriate
value by either catting to the appropriate /proc entry or changing the
/usr/src/linux/include/asm/shmparam.h.

        Otherwise the shared memory on alpha should be fully functional and I
see no reason to disable it. Mine are bumped up to 32 or more on most
machines.

        And If I recall correctly the comments in that file are actually
wrong. Value is not bytes, but in machine size word. For alpha *8.

        As I said - I do not run X on them so all #include "stdisclaimer.h"
apply.

-------------------------------------------------------------------------------

- SCO Unix - configure spus�te takto:
        CFLAGS="-belf -DANSICPP" ./configure

- SunOS, Solaris
        Kdy� m�te naistalovan� gcc, tak configure spus�te takto:
        CPP_PATH="gcc -E -x c" ./configure
        Preprocesoru cpp od Sunu chyb�j� n�kter� vlastnosti, kter� Window Maker
        pot�ebuje, a to m��e zp�sobit probl�my b�hem parsov�n� konfigura�n�ch
        soubor�. Je mo�n�, �e budete muset pou��t --with-libs-from a
        --with-incs-from k nahrazen� adres��e s libtiff.
        N�kdo doporu�uje pou��t /usr/local/lib jako prvn� cestu v LD_LIBRARY_PATH.

        Kdy� m�te Ultra Creator 3D nebo jinou high-end grafickou kartu, tak se
        ujist�te, �e X server startuje s 24 bitovou barevnou hloubkou, jinak
        m��ete m�t probl�my s pom�ch�n�m barev. Toto je chyba Window Makeru,
        kter� bude odstran�na.

- GNU/Linux obecn�
        Ujist�te se, �e soubor /etc/ld.so.conf obsahuje ��dek "/usr/local/lib".
        Odinstalujte jakoukoliv star�� verzi bal��ku Window Makeru p�ed instalac�
        nov�j�� verze.
        Nezapome�te spustit ldconfig po instalaci Window Makeru.

- RedHat GNU/Linux
        RedHat m� n�kolik obt�uj�c�ch chyb. Pokud ho pou��v�te dodr�ujte n�kolik
        n�sleduj�c�ch krok�, jinak v�m Window Maker nebude fungovat.

        * pokud m�te nainstalovan� Window Maker z distribuce RedHat, tak ho p�ed
        upgradem odinstalujte

        * ujist�te se, �e nem�te syst�mov� prom�nn� LANG a LINGUAS nastaven�
        na en_RN

        * ujist�te se, �e va�e syst�mov� prom�nn� PATH obsahuje polo�ku
        /usr/local/bin

        * ujist�te se, �e soubor /etc/ld.so.conf obsahuje ��dek "/usr/local/lib"
        p�ed t�m, ne� spust�te ldconfig (na konci instalace)

        * pokud m�te probl�my, kter� se projevuj� chybovou hl�kou, kter�
        obsahuje text --no-reexec, tak odinstalujte libtool-1.2b a nainstalujte
        si nov�j�� verzi libtool-1.3. libtool-1.3 m��ete nal�zt na adrese:
        ftp.gnu.org  .    P�e�t�te si tak� odstavec �E�EN� PROBL�M�.

        * pokud m�te nainstalovan� bal��ek Window Maker od RedHatu a nyn�
        instalujete novou verzi "ru�n�" (kompilov�n�m zdrojov�ch k�d�), tak
        nejprve odinstalujte st�vaj�c� bal��ek.

        * ujist�te se, �e se na va�em syst�mu nach�z� symbolick� link z
        /usr/include/X11 na /usr/X11R6/include/X11. Pokud tomu tak nen�, tak
        na p��kazovou ��dku napi�te:

         ln -s /usr/X11R6/include/X11 /usr/include/X11

        * ujist�te se, �e m�te symbolick� link /lib/cpp ukazuj�c� na cpp
        program

        Pokud pochybujete o n�jak�m z p�edch�zej�ch krok�, tak nev�hejte
        kontaktovat u�ivatelskou podporu distribuce RedHat. Oni v�m laskav�
        zodpov� v�echny va�e dotazy zohled�uj�c� v� syst�m. Oni v�d�
        mnohem v�ce o va�em (jejich) syst�mu ne� my (my nepou��v�me
        RedHat).

- PowerPC MkLinux
        Budete pot�ebovat posledn� verzi Xpma. Star�� verze pravd�podobn� 
        obsahuj� chybu, kter� zp�sobuje zamrznut� syst�mu.

- Debian GNU/Linux
        Pokud chcete podporu JPEG a TIFF, tak se ujist�te, �e m�te nainstalov�ny
        bal��ky libtiff-dev a libjpeg-dev.

- SuSE GNU/Linux
        Pokud m�te ji� nainstalov�n bali�ek Window Maker od SuSE, tak ho
        odstra�te ne� se pust�te do kompilace Window Makeru. kdy� tak
        neu�in�te, budete m�t probl�my.

- MetroX (nezn�m� verze)
        Metrox obsahuje chybu, kter� zap�i�i�uje, �e obr�zky, kter� jsou
        nastaveny jako pozad�, jsou po�kozeny. Pokud pou��v�te Metrox a
        m�te podivn� probl�my s texturami, tak nepou��vejte textury v
        titulc�ch nebo pou��vejte jin� X server.

INSTALACE
=========

Nejjednodu��� zp�sob, jak nainstalovat Window Maker, je spustit skript
Install nebo Install.cs (ten s v�mi komunikuje �esky). Oba skripty
v�s jednodu�e provedou celou instalac�.

        su
        Install.cs

Pozn�mka: tato metoda neposkytuje v�echny mo�nosti konfigurace a pokud
          se setk�te s n�jak�mi probl�my, tak stejn� budete muset
          pou��t n�sleduj�c� zp�sob kompilace.

Kompilace Window Makeru
-----------------------
        Pro osv�d�en� zp�sob zadejte n�sleduj�c� p��kazy v shellu:

        ./configure
        make

pak se p�ihla�te jako root a zadejte:

        make install
        ldconfig

pokud nejste program�tor a nebudete ladit Window Maker, tak se m��ete zbavit
lad�c�ch symbol� v bin�rn�ch souborech a zmen�it jejich velikost:

        make install-strip
        ldconfig

Takto zkompilujete a nainstalujete Window Maker se standartn�mi parametry.

Pokud chcete upravit n�kter� vlastnosti, tak mus�te u�init n�sleduj�c�:

        1. (voliteln�) Pod�vejte se na ��st MO�NOSTI KONFIGURACE, kde jsou
        uveden� mo�nosti konfigurace. Nebo spus�te:

        ./configure --help

        tak dostanete kompletn� seznam v�ech dostupn�ch mo�nost� konfigurace.

        2. Spus�te ./configure s mo�nost�, kterou jste si vybrali. Nap��klad,
        pokud chcete pou��t mo�nost --enable-kde, tak zadejte:

        ./configure --enable-kde

        3. (voliteln�) Otev�ete soubor ./src/wconfig.h va��m obl�ben�m editorem
        a upravte n�kter� mo�nosti, kter� si p�ejete zm�nit.

        4. Kompilace. Zadejte pouze:

        make

        5. P�ihlaste se jako root (pokud tak nem��etet u�init, tak si p�e�t�te
        ��st "Nem�m rootovsk� helso :-(") a nainstalujte Window Maker na v�
        syst�m:

        su root
        make install

Nastaven� specifick� pro u�ivatele
----------------------------------

Tyto instrukce nejsou povinn�, pokud upgradujete Window Maker ze star��
verze na nov�j�� a pokud nen� uvedeno jinak v souboru NEWS.

Ka�d� u�ivatel na va�em syst�mu, kter� si p�eje pou��vat Window Maker mus�
ud�lat n�sleduj�c�:

        1. Nainsatlovat konfigura�n� soubory Window Makeru do jeho domovsk�ho
        adres��e:

        wmaker.inst

        wmaker.inst nainstaluje konfigura�n� soubory a nastav� X server tak,
        aby automaticky spou�t�l Window Maker p�i jejich spu�t�n�.

        To je v�echno, p��tel�.

        Informace o konfiguraci a spoust� ostatn�ch v�c� v�m poskytne:

        man wmaker

Pro hlub�� �vod do Window Makeru si p�e�t�te U�ivatelskou p��ru�ku (User Guide).

M�li byste se tak� pod�vat na FAQ (Frequently Asked Questions = �asto kladen� 
ot�zky), pokud budete m�t n�jak� probl�my/pot�e jak p�i samotn� kompilaci,
tak s u��v�n�m Window Makeru.

Instalov�n� speci�ln�ho bal��ku
-------------------------------

Rozbalte WindowMaker-extra-<��slo_verze>.tar.gz v adres��i /usr/local/share

Tento soubor si m��ete sehnat na adrese: ftp://ftp.windowmaker.org. Instalace
tohoto souboru v�bec nen� nutn�. tento bal��ek obsahuje n�kolik ikon a t�mat.
Hledejte posledn� dostupnou verzi. V bal��ku tak� naleznete soubor
WindowMaker-extra.readme, kter� v�m porad�, co m�te ud�lat.

Nem�m rootovsk� helso :-(
-------------------------

Pokud nem�te superu�ivatelsk� privilegia (nem��ete se p�ihl�sit jako root),
tak nezoufejte, proto�e m��ete nainstalovat Window Maker do va�eho vlastn�ho
domovsk�ho adres��e. K tomu mus�te pou��t volbu --prefix p�i spu�t�n�
./configure. Tak� mus�te pou��t volbu --with-appspath, kter� specifikuje
cestu pro WPrefs.app.
P��klad:

./configure --prefix=/home/karel --with-appspath=/home/karel/GNUstep/Applications

Potom p�idejte adres�� /home/karel/bin do syst�mov� prom�nn� PATH a adres��
/home/karel/lib do syt�mov� prom�nn� LD_LIBRARY_PATH a nakonec spus�te
~/bin/wmaker.inst.

Samoz�ejm�, �e adres�� /home/karel bude ve va�em p��pad� nahrazen va��m
vlastn�m domovsk�m adres��em.


UPGRADE
=======

Pokud upgradujete ze star�� verze Window Makeru:

        1. Nakonfigurujte a zkompilujte Window Maker jako obvykle.
        2. Nainstalujte Window Maker (ale nespou�t�jte wmaker.inst).
        3. P�e�t�te si soubor NEWS a aktualizujte va�e konfigura�n� soubory,
           pokud je to nezbytn�.

�E�EN� PROBL�M�
===============

Pokud m�te n�jak� probl�my b�hem konfigurace (kdy� b�� configure), jako
nap��klad neschopnost pou��t knihovnu grafick�ho form�tu, o kter�m v�te, �e
ho m�te nainstalov�n, tak se pod�vejte do souboru config.log. Mo�n� zde
najdete p���inu sv�ch probl�m�.

== Error with loading fonts, even if they exist.

Zkuste kompilaci bez podpory NLS (n�rodn�ho prost�ed�).

== Error when configuring

ltconfig: unrecognized option `--no-reexec'
Try `ltconfig --help' for more information.
configure: error: libtool configure failed

odstra�te volbu --no-reexec ze souboru aclocal.mc a spus�te znovu configure.
Tak� zkontrolujte, zda verze autoconfu a automaku, kter� m�te nainsatlovan�
odpov�daj� n�e uveden�m hodnot�m:
autoconf 2.13
automake 1.4
libtool 1.3

Pozn�mka: nem��e to b�t libtool 1.2b, ale mus� to b�t libtool 1.3 ze str�nek
GNU.

== configure doesn't detect libtiff, or other graphic libraries.

Sma�te soubor config.cache, pak znovu spus�te configure s n�sleduj�c�mi
volbami (a jin�mi, kter� pou��v�te):
--with-libs-from="-L/usr/local/lib"
--with-incs-from="-I/usr/local/include -I/usr/local/include/tiff"
Na p��slu�n� m�sta vlo�te cesty k va��m grafick�m knihovn�m a odpov�daj�c�m
hlavi�kov�m soubor�m. M��ete zadat n�kolik cest do t�chto voleb, jako je to
ve v��e uveden�m p��klad� --with-incs-from. Jenom je nezapome�te odd�lit
mezerou.

== configure doesn't detect libXpm.

* Zkontrolujte, jestli m�te symbolick� link ze souboru libXpm.so.4.9 na
  soubor libXpm.so

== Segmentation fault on startup

* Zkontrolujte, jestli verze knihovny libXPM je vy��� ne� 4.7

* Zkontrolujte, zda-li m�te upravenou verzi ~/GNUstep/Defaults/WindowMaker
  Pokud si nejste jisti, tak zkuste p�ejmenovat ~/GNUstep na ~/GNUtmp a
  spus�te wmaker.inst

== "...: your machine is misconfigured. gethostname() returned (none)"

* Jm�no va�eho po��ta�e je nastaveno nespr�vn�, proto�e za��n� uvozovkami.
  Spus�te man hostname a zde se dozv�te, jak zm�nit jm�no va�eho po��ta�e.

== The root menu contains only 2 entries. ("XTerm" and "Exit...")

* Window Maker nem��e nal�zt cpp (preprocesor jazyka C). Pokud se v� cpp
  nenach�z� v /lib/cpp, tak otev�te soubor src/config.h a nastavte spr�vn�
  cestu CPP_PATH.

== checking lex output file root... configure: error: cannot find output from true; giving up

* P�e�t�te si odstavec PO�ADAVKY na za��tku tohoto souboru.

M�STN� NASTAVEN� / INTERNACIONALIZACE
=====================================

Window Maker m� podporu n�rodn�ch jazyk�. Aby jste ji povolili, tak
mus�te zkompilovat Window Maker s n�kolika dal��mi parametry.
Seznam podporovan�ch jazyk� naleznete v souboru ./po/README.

0 - Mus�te m�t nainstalovan� bal��ek GNU gettextu. Tento bal��ek
    m��ete nal�zt na ftp://prep.ai.mit.edu/pub/gnu/gettext-nnn.tar.gz

Kroky 1,2 a 3 m��ete vynechat, pokud pou��v�te skript Install.cs nebo
skript Install.

1 - Vyberte si jazyky, kter� budete cht�t pou��vat. Zadejte seznam
    t�chto jazyk� do syst�mov� prom�nn� LINGUAS. Angli�tina je
    podporov�na v�dy. P��klady

    C - shell:

        setenv LINGUAS "pt ja de"

    Bash(sh):

        export LINGUAS
        LINGUAS="pt ja de"

    P�e�t�te si soubor po/README pokud chcete p�elo�it Window Maker
    pro n�jak� dal�� jazyk.

2 - Nav�c, pokud v� jazyk pou��v� multi-byte znaky, nap��klad Japon�tina
    nebo Korej�tina, tak mus�te nastavit volbu the MultiByteText na YES
    v souboru ~/GNUstep/Defaults/WMGLOBAL

3 - Nakonfigurujte, zkompilujte a nainstalujte Window Maker jako obvykle.

4 - N�rodn� prost�ed� si m��ete zm�nit i za b�hu Window Makeru. Syst�movou
    prom�nnou LANG nastav�te na v�mi zvolenou hodnotu. Nap��klad, pokud
    chcete pou��t portugalsk� prost�ed�, mus�te spustit:

    C - shell:

        setenv LANG pt

    Bourne shell a podobn�:

        export LANG
        LANG=pt

    Nakonec mus�te restartovat/spustit Window Maker.

    Pozn�mka: Kdy� m�te nastavenou syst�movou prom�nnou LC_TYPE, tak j�
    mus�te zru�it p�ed spu�t�n�m Window Makeru.

    Window Maker hled� soubory s definic� menu v tomto po�ad� (pro
    brazilskou portugal�tinu):

        menu.pt_BR
        menu.pt
        menu

5 - Pokud si vyberete jazyk, kter� pou��v� multi-byte znaky, tak mus�te
    p��slu�n�m zp�sobem nastavit fonty. P�e�t�te si manu�lov� str�nky
    o XCreateFontSet k z�sk�n� v�t��ho mno�stv� informac� o dan�m
    probl�mu. Mus�te zm�nit v souboru ~/GNUstep/Default/WindowMaker
    nastaven� font� pro titulky, menu, atd. Fonty pro dialogy nastav�te
    v souboru ~/GNUstep/Default/WMGLOBAL. �et�zce %d ve jm�nech font�
    nemus� b�t odstran�n�. Tak� m��ete pou��t skript wsetfont, kter�
    toto v�e u�in� za v�s. Pokud se ho rozhodnote pou��t, tak si k n�mu
    p�e�t�te instrukce tak, �e spust�te wsetfont bez argument�.

    P��klad ��sti souboru ~/GNUstep/Default/WindowMaker:

        WindowTitleFont = "-*-helvetica-bold-r-normal-*-12-*,-*-*-medium-r-normal-*-14-*";
        MenuTitleFont = "-*-helvetica-bold-r-normal-*-12-*,-*-*-medium-r-normal-*-14-*";
        MenuTextFont = "-*-helvetica-medium-r-normal-*-12-*,-*-*-medium-r-normal-*-14-*";
        IconTitleFont = "-*-helvetica-medium-r-normal-*-8-*,-*-*-medium-r-normal-*-12-*";
        ClipTitleFont = "-*-helvetica-bold-r-normal-*-10-*,-*-*-medium-r-normal-*-12-*";
        DisplayFont = "-*-helvetica-medium-r-normal-*-12-*,-*-*-medium-r-normal-*-12-*";

    a souboru ~/GNUstep/Default/WMGLOBAL:

        SystemFont = "-*-*-medium-r-normal-*-%d-*-*-*-*-*-*-*";
        BoldSystemFont = "-*-*-medium-r-normal-*-%d-*-*-*-*-*-*-*";

    Tyto dva fonty jsou pou��v�ny v aplikac�ch, kter� pou��vaj� WINGs (WindowMaker a
    WPrefs.app).

    Skript wsetfont v�m umo�n� nastavit fonty mnohem jednodu��m zp�sobem. Pod�vejte
    se na jeho manu�lov� str�nku k z�sk�n� bli���ch informac�.