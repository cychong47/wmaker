                �asto kladen� ot�zky na podporu m�stn�ho nastaven�
                ==================================================

Pokud v�m nefunguje podpora I18N, tak zkontrolujte tato nastaven�:

        - syst�mov� prom�nn� LANG mus� b�t nastaven� tak, aby odpov�dala va�emu
          m�stn�mu nastaven� (�e�tina = czech), va�e m�stn� nastaven� mus� b�t
          podporovateln� va��m opera�n�m syst�mem nebo X emulac�. V�echny
          podporovateln� lokalizace zobraz�te p��kazem "locale -a". M�li byste
          tak� zkontrolovat, zda-li je va�e m�stn� nastaven� podporovan�
          X emulac�. Soubor: "/usr/X11R6/lib/X11/locale/locale.alias" by m�l
          obsahovat podobnou sekvenci (podpora pro �e�tinu):

                cs                              cs_CZ.ISO8859-2
                cs_CS                           cs_CZ.ISO8859-2
                cs_CS.ISO8859-2                 cs_CZ.ISO8859-2
                cs_CZ                           cs_CZ.ISO8859-2
                cs_CZ.iso88592                  cs_CZ.ISO8859-2
                cz                              cz_CZ.ISO8859-2
                cz_CZ                           cz_CZ.ISO8859-2

        - zkontrolujte pou�it� spr�vn�ch font� pro va�e m�stn� nastaven�.
          Pokud nepou��v�te spr�vn� fonty s k�dov�n�m, kter� je nastaveno v
          Xlib nebo libc, tak se m��ou d�t "dost divn� v�ci". Zkuste explicitn�
          zadat kov�n� do prom�nn� LANG: LANG=cs_CS.ISO8859-2 nebo
          LANG=cs_CZ.iso88592 a znovu zkontrolujte:
          "/usr/X11R6/lib/X11/locale/locale.alias"

        - pokud v� opera�n� syst�m nepodporuje m�stn� nastaven� (locales), nebo
          pokud v� OS nepodporuje m�stn� nastaven� pro v� jazyk, m��ete
          pou��t emulaci m�stn�ho nastaven� X Window Syst�mu. Zprovoznit tuto
          emulaci je mo�n� spu�t�n�m ./configure s volbou "--witn-x-locale".
          Pokud pou��v�te n�jak� komer�n� syst�m jako je nap��klad IRIX, AIX,
          Solaris, ...,tak asi X emulaci nebudete pot�ebovat. Ov�em pokud je
          va��m opera�n�m syst�mem Linux, NetBSD nebo jin� u�asn�, voln�
          �i�iteln� opera�n� syst�m, tak je mo�n�, �e va�e m�stn� nastaven�
          zat�m nen� podporovan�. Potom pou�ijte volbu "--witn-x-locale".

          Pozn: Aby jste mohli pou��vat X emulaci m�stn�ch nastaven�, tak va�e
                Xlib mus� b�t zkompilovan� s touto podporou. Xlib v RedHat 5.0
                tak zkompilovan� nejsou (RH4.x jsou OK). P�ekompilovan� Xlib
                s podporou pro emulac� m�stn�ch nastaven� pro RH5.0 jsou
                dostupn� na adrese:

                ftp://ftp.linux.or.jp/pub/RPM/glibc

        - fonty, kter� pou��v�te by m�li b�t podporovan� va��m m�stn�m nastaven�m.
          Jestli�e va�e nastaven� font� v souboru ~/GNUstep/Defaults/WindowMaker
          vypad� takto:

          WindowTitleFont = "-*-helvetica-bold-r-normal-*-12-*-*-*-*-*-*-*";
          MenuTitleFont = "-*-helvetica-bold-r-normal-*-12-*-*-*-*-*-*-*";  ,

          nem��ete zobrazovat znaky jin� ne� iso8859-x ve fontu helvetica.
          Jednoduch� zp�sob, jak zobrazovat znaky r�zn�ch jazyk�, je nastavit v�echny
          fonty takto:

                "-*-*-medium-r-normal-*-14-*-*-*-*-*-*-*"

          Tak� je nutn� zm�nit nastaven� font� v souborech styl� v adres��i:
          ~/Library/WindowMaker/Style.

        - pokud si nejste jisti, zda-li m� syst�mov� prom�nn� LC_TYPE spr�vnou
          hodnotu, tak ji nenastavujte.