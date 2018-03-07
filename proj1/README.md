<h1><span><a name="Projekt_1_-_Práce_s_textem">Projekt 1 - Práce s textem</a></span></h1>

<h2><span><a name="Motivační_příklad">Motivační příklad</a></span></h2>

<p>

Představme si virtuální klávesnici v navigaci na palubní desce auta. Navigace má celou databázi adres a očekává od uživatele vstup pomocí virtuální klávesnice. Aby se vstup uživateli usnadnil, jsou na klávesnici v daném okamžiku povoleny pouze vybrané klávesy - ty klávesy, při jejichž použití by vyhledáváný řetězec stále vedl ke známé adrese. Například navigace zná města Brno, Beroun a Bruntál, uživatel již zadal písmena &quot;BR&quot; a na navigaci budou tedy povoleny pouze klávesy &quot;N&quot; (vedoucí k &quot;Brno&quot;) a &quot;U&quot; (vedoucí k &quot;Bruntál&quot;).
</p>

<h2><span><a name="Popis_projektu">Popis projektu</a></span></h2>

<p>

Cílem projektu je vytvořit program, který by emuloval algoritmus výpočtu povolení a zakázání kláves na virtuální klávesnici navigace. Vstupem programu jsou data známých adres a uživatelem zadaný řetězec. Výstup programu bude obsahovat znaky, které mají být na klávesnici povoleny.
</p>

<h2><span><a name="Detailní_specifikace">Detailní specifikace</a></span></h2>

<p>

Program implementujte ve zdrojovém souboru <i>proj1.c</i>. Vstupní data budou čtena ze standardního vstupu (stdin), výstup bude tisknut na standardní výstup (stdout).
</p>

<h3><span><a name="Překlad_a_odevzdání_zdrojového_souboru">Překlad a odevzdání zdrojového souboru</a></span></h3>

<p>

Odevzdání: Odevzdejte zdrojový soubor <i>proj1.c</i> prostřednictvím informačního systému.
</p>

<p>

Překlad: Program překládejte s následujícími argumenty
</p>
<pre>$ gcc -std=c99 -Wall -Wextra -Werror proj1.c -o proj1</pre>

<h3><span><a name="Syntax_spuštění">Syntax spuštění</a></span></h3>

<p>

Program se spouští v následující podobě: (./proj1 značí umístění a název programu):
</p>
<pre>./proj1 ADRESA</pre>

<p>

Pokud je program spuštěn bez argumentů, bere zadanou adresu jako prázdný řetězec.
</p>

<h3><span><a name="Implementační_detaily">Implementační detaily</a></span></h3>

<h4><span><a name="Vstupní_databáze_adres">Vstupní databáze adres</a></span></h4>

<p>

Databáze adres jsou textová data, u kterých každý řádek označuje jednu adresu. Každý řádek obsahuje maximálně 100 znaků. Seznam adres je neuspořádaný. U všech dat nezáleží na velikosti písmen (tzv. case insensitive). Program musí podporovat alespoň 42 adres.
</p>

<h4><span><a name="Výstup_programu">Výstup programu</a></span></h4>

<p>

Výstup programu může být trojího druhu:
</p>

<ul>
<li class="level1">adresa nalezena,</li>
<li class="level1">adresa vyžaduje specifikaci,</li>
<li class="level1">adresa nenalezena.</li>
</ul>

<h5><span><a name="Adresa_nalezena">Adresa nalezena</a></span></h5>
<pre>Found: S</pre>

<p>

Tento výstup se tiskne, pokud je v databázi adres nalezena jediná adresa <tt>S</tt>, jejíž prefix odpovídá uživatelem zadané adrese <tt>ADRESA</tt>. (Pozn. <a href="https://en.oxforddictionaries.com/definition/prefix" class="external" title="https://en.oxforddictionaries.com/definition/prefix"  rel="nofollow">prefix</a> P řetězce S je takový řetězec, u kterého řetězec S začíná řetězcem P).
</p>

<h5><span><a name="Adresa_vyžaduje_specifikaci">Adresa vyžaduje specifikaci</a></span></h5>
<pre>Enable: CHARS</pre>

<p>

Pokud je v databázi adres nalezeno více adres odpovídající danému prefixu <tt>ADRESA</tt>, program pomocí takto naformátovaného řádku vytiskne seznam povolených kláves CHARS. CHARS je abecedně seřazený seznam znaků, u nichž pro každý znak <tt>C</tt> platí, že v databázi adres existuje adresa, jejíž prefix odpovídá spojení řetězce <tt>ADRESA</tt> s daným znakem <tt>C</tt>.
</p>

<h5><span><a name="Adresa_nenalezena">Adresa nenalezena</a></span></h5>
<pre>Not found</pre>

<p>

Pokud v databázi adres neexistuje adresa, jejíž prefix by odpovídal zadanému řetězci <tt>ADRESA</tt>, vytiskne program toto hlášení.
</p>

<h4><span><a name="Omezení_v_projektu">Omezení v projektu</a></span></h4>

<p>

Je zakázané použít následující funkce:
</p>

<ul>
<li class="level1">volání z rodiny malloc a free - práce s dynamickou pamětí není v tomto projektu zapotřebí,</li>
<li class="level1">volání z rodiny fopen, fclose, fscanf, ... - práce se soubory (dočasnými) není v tomto projektu žádoucí,</li>
<li class="level1">volání qsort, lsearch, bsearch a hsearch - cílem je zamyslet se nad algoritmizací a strukturou dat.</li>
</ul>

<h3><span><a name="Neočekávané_chování">Neočekávané chování</a></span></h3>

<p>

Na chyby za běhu programu reagujte obvyklým způsobem: Na neočekávaná vstupní data, formát vstupních dat nebo chyby při volání funkcí reagujte přerušením programu se stručným a výstižným chybovým hlášením na příslušný výstup a odpovídajícím návratovým kódem. Hlášení budou v kódování ASCII česky nebo anglicky.
</p>

<h3><span><a name="Příklady_vstupů_a_výstupů">Příklady vstupů a výstupů</a></span></h3>

<p>

Pomocný soubor adres:
</p>
<pre>$ cat adresy.txt
Praha
Brno
Bruntal
Bratislava</pre>

<p>

Příklad hledání slova brno
</p>
<pre>$ ./proj1 &lt;adresy.txt
Enable: BP</pre>
<pre>$ ./proj1 b &lt;adresy.txt
Enable: R</pre>
<pre>$ ./proj1 br &lt;adresy.txt
Enable: ANU</pre>
<pre>$ ./proj1 brn &lt;adresy.txt
Found: BRNO</pre>
<pre>$ ./proj1 be &lt;adresy.txt
Not found</pre>

<h2><span><a name="Hodnocení">Hodnocení</a></span></h2>

<p>

Na výsledném hodnocení mají hlavní vliv následující faktory:
</p>

<ul>
<li class="level1">přeložitelnost zdrojového souboru,</li>
<li class="level1">formát zdrojového souboru (členění, zarovnání, komentáře, vhodně zvolené identifikátory),</li>
<li class="level1">dekompozice problému na podproblémy (vhodné funkce, vhodná délka funkcí a parametry funkcí),</li>
<li class="level1">správná volba datových typů, případně tvorba nových typů,</li>
<li class="level1">správná funkcionalita vyhledání kláves a</li>
<li class="level1">ošetření chybových stavů.</li>
</ul>
