<h1><span><a name="Projekt_2_-_Iterační_výpočty">Projekt 2 - Iterační výpočty</a></span></h1>

<h2><span><a name="Motivační_příklad">Motivační příklad</a></span></h2>

<p>

Mějme přístroj obsahující sensor náklonu a procesor umožňující jednoduché operace nad čísly s plovoucí řádovou čárkou. Přístroj chce uživatel používat pro měření vzdálenosti a výšky velkých objektů (budova, komín, strom).
</p>

<p>

<a href="cwk.php.cs?title=IZP:Projekt2&amp;src=Diagram.png&amp;ns=IZP&amp;&amp;action=fileinfo&amp;csid=649642&amp;id=12214" class="media" title="Diagram.png"><img src="cwk.php.cs?title=IZP:Projekt2&amp;src=Diagram.png&amp;ns=IZP&amp;action=download&amp;csid=649642&amp;id=12214" class="media " alt="" /></a>
</p>

<h2><span><a name="Zadání_projektu">Zadání projektu</a></span></h2>

<p>

Implementujte funkce nutné pro výpočet vzdálenosti a výšky pomocí úhlu náklonu měřeného přístroje. Výpočet proveďte pouze pomocí matematických operací +,-,*,/. Implementujte výpočet vzdálenosti a výšky měřeného objektu.
</p>

<h3><span><a name="Překlad_a_odevzdání_zdrojového_souboru">Překlad a odevzdání zdrojového souboru</a></span></h3>

<p>

Odevzdání: Program implementujte ve zdrojovém souboru <tt>proj2.c</tt>. Zdrojový soubor odevzdejte prostřednictvím informačního systému.
</p>

<p>

Překlad: Program překládejte s následujícími argumenty:<pre>$ gcc -std=c99 -Wall -Wextra -Werror proj2.c -lm -o proj2</pre>

</p>

<h3><span><a name="Syntax_spuštění">Syntax spuštění</a></span></h3>

<p>

Program se spouští v následující podobě:<pre>./proj2 --help</pre>

nebo<pre>./proj2 --tan A N M</pre>

nebo<pre>./proj2 [-c X] -m A [B]</pre>

</p>

<p>

Argumenty programu:
</p>

<ul>
<li class="level1"><tt>--help</tt> způsobí, že program vytiskne nápovědu používání programu a skončí.</li>
<li class="level1"><tt>--tan</tt> porovná přesnosti výpočtu tangens úhlu <tt>A</tt> (v radiánech) mezi voláním <tt>tan</tt> z matematické knihovny, a výpočtu tangens pomocí Taylorova polynomu a zřetězeného zlomku. Argumenty <tt>N</tt> a <tt>M</tt> udávají, ve kterých iteracích iteračního výpočtu má porovnání probíhat. 0 &lt; N &lt;= M &lt; 14</li>
<li class="level1"><tt>-m</tt> vypočítá a změří vzdálenosti.
<ul>
<li class="level2">Úhel &alpha; (viz obrázek) je dán argumentem <tt>A</tt> v radiánech. Program vypočítá a vypíše vzdálenost měřeného objektu. 0 &lt; A &lt;= 1.4 &lt; &pi;/2.</li>
<li class="level2">Pokud je zadán, úhel &beta; udává argument <tt>B</tt> v radiánech. Program vypočítá a vypíše i výšku měřeného objektu. 0 &lt; B &lt;= 1.4 &lt; &pi;/2</li>
<li class="level2">Argument <tt>-c</tt> nastavuje výšku měřicího přístroje c pro výpočet. Výška c je dána argumentem X (0 &lt; X &lt;= 100). Argument je volitelný - implicitní výška je 1.5 metrů.</li>
</ul>
</li>
</ul>

<h3><span><a name="Implementační_detaily">Implementační detaily</a></span></h3>

<p>

Je zakázané použít funkce z matematické knihovny. Jedinou výjimkou jsou funkce:
<div class="c syntax" style="font-family:monospace;"><pre style="font: normal normal 1em/1.2em monospace; margin:0; padding:0; background:none; vertical-align:top;"><span style="color: #339933;">#include &lt;math.h&gt;</span>
<span style="color: #993333;">double</span> <a href="http://www.opengroup.org/onlinepubs/009695399/functions/tan.html"><span style="color: #000066;">tan</span></a><span style="color: #009900;">&#40;</span><span style="color: #993333;">double</span> x<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span> <span style="color: #666666; font-style: italic;">// pro účely porovnání výpočtů</span>
<span style="color: #993333;">int</span> isinf<span style="color: #009900;">&#40;</span>x<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span>
<span style="color: #993333;">int</span> isnan<span style="color: #009900;">&#40;</span>x<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span>
<span style="color: #993333;">double</span> <a href="http://www.opengroup.org/onlinepubs/009695399/functions/fabs.html"><span style="color: #000066;">fabs</span></a><span style="color: #009900;">&#40;</span><span style="color: #993333;">double</span> x<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span></pre></div>
a konstanty NAN a INF. Ve všech výpočtech používejte typ <tt>double</tt>. Uvažujte přesnost na 10 míst. Počet iterací v iteračních výpočtech odvoďte.
</p>

<h4><span><a name="Implementace_tangens">Implementace tangens</a></span></h4>

<p>

Funkci tangens implementujte dvakrát a to pomocí Taylorova polynomu a zřetězených zlomků.
</p>

<h5><span><a name="podúkol">1. podúkol</a></span></h5>

<p>

Tangens pomocí Taylorova polynomu implementujte ve funkci s prototypem:
<div class="c syntax" style="font-family:monospace;"><pre style="font: normal normal 1em/1.2em monospace; margin:0; padding:0; background:none; vertical-align:top;"><span style="color: #993333;">double</span> taylor_tan<span style="color: #009900;">&#40;</span><span style="color: #993333;">double</span> x<span style="color: #339933;">,</span> <span style="color: #993333;">unsigned</span> <span style="color: #993333;">int</span> n<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span></pre></div>
kde x udává úhel a n rozvoj polynomu (počet členů). Taylorův polynom pro funkci tangens vypadá následovně:
</p>

<p>

<a href="cwk.php.cs?title=IZP:Projekt2&amp;src=Taylor_tan.png&amp;ns=IZP&amp;&amp;action=fileinfo&amp;csid=649642&amp;id=12214" class="media" title="taylor_tan.png"><img src="cwk.php.cs?title=IZP:Projekt2&amp;src=Taylor_tan.png&amp;ns=IZP&amp;action=download&amp;csid=649642&amp;id=12214" class="media " alt="" /></a>
</p>

<p>

přičemž řada čitatelů ve zlomcích koeficientů je <a href="https://oeis.org/A002430" class="external" title="https://oeis.org/A002430"  rel="nofollow">zde</a> a řada jmenovatelů ve zlomcích koeficientů je <a href="https://oeis.org/A156769" class="external" title="https://oeis.org/A156769"  rel="nofollow">zde</a>. Ve svém programu použijte pouze 13 prvních koeficientů.
</p>

<h5><span><a name="podúkol1">2. podúkol</a></span></h5>

<p>

Tangens pomocí zřetězených zlomků (viz demonstrační cvičení) implementujte ve funkci s prototypem:
<div class="c syntax" style="font-family:monospace;"><pre style="font: normal normal 1em/1.2em monospace; margin:0; padding:0; background:none; vertical-align:top;"><span style="color: #993333;">double</span> cfrac_tan<span style="color: #009900;">&#40;</span><span style="color: #993333;">double</span> x<span style="color: #339933;">,</span> <span style="color: #993333;">unsigned</span> <span style="color: #993333;">int</span> n<span style="color: #009900;">&#41;</span><span style="color: #339933;">;</span></pre></div>
kde x udává úhel a n rozvoj zřetězeného zlomku:
</p>

<p>

<a href="cwk.php.cs?title=IZP:Projekt2&amp;src=Tan1.png&amp;ns=IZP&amp;&amp;action=fileinfo&amp;csid=649642&amp;id=12214" class="media" title="tan1.png"><img src="cwk.php.cs?title=IZP:Projekt2&amp;src=Tan1.png&amp;ns=IZP&amp;action=download&amp;csid=649642&amp;id=12214" class="media " alt="" /></a>
</p>

<p>

nebo 
</p>

<p>

<a href="cwk.php.cs?title=IZP:Projekt2&amp;src=Tan2.png&amp;ns=IZP&amp;&amp;action=fileinfo&amp;csid=649642&amp;id=12214" class="media" title="tan2.png"><img src="cwk.php.cs?title=IZP:Projekt2&amp;src=Tan2.png&amp;ns=IZP&amp;action=download&amp;csid=649642&amp;id=12214" class="media " alt="" /></a>
</p>

<h5><span><a name="Porovnání_přesnosti_výpočtu_tangens">Porovnání přesnosti výpočtu tangens</a></span></h5>

<p>

Porovnání iteračních a zabudovaných výpočtů realizujte pro zadaný počet iterací. Výstup porovnání bude v podobě řádků obsahující následující:
</p>

<p>
<pre>I M T TE C CE</pre>

</p>

<p>

(odpovídající formátu &quot;%d %e %e %e %e %e\n&quot;), kde:
</p>

<ul>
<li class="level1"><tt>I</tt> značí počet iterací iteračního výpočtu,</li>
<li class="level1"><tt>M</tt> výsledek z funkce <tt>tan</tt> matematické knihovny,</li>
<li class="level1"><tt>T</tt> výsledek z funkce <tt>taylor_tan</tt>,</li>
<li class="level1"><tt>TE</tt> absolutní chybu mezi výpočtem pomocí Taylorova polynomu a matematickou knihovnou,</li>
<li class="level1"><tt>C</tt> výsledek z funkce <tt>cfrac_tan</tt> a</li>
<li class="level1"><tt>CE</tt> absolutní chybu mezi výpočtem pomocí zřetězených zlomků a matematickou knihovnou.</li>
</ul>

<p>

Počet iterací udává interval daný argumenty programu <tt>&lt;N;M&gt;</tt>. Výstup programu tedy bude obsahovat N-M+1 řádků. První řádek tedy začíná číslem N.
</p>

<h4><span><a name="Měření">Měření</a></span></h4>

<p>

Pro měření vzdálenosti a výšky použijte vámi implementovanou funkci <tt>cfrac_tan</tt>. 
</p>

<p>

V případě zadaného úhlu &alpha; i &beta; vypište dvě čísla odpovídající délce d a výšce v (v tomto pořadí). Oba číselné údaje vypisujte formátovaným výstupem pomocí <tt>&quot;%.10e&quot;</tt>, každý údaj samostatně na jeden řádek. 
</p>

<h3><span><a name="Příklady_vstupů_a_výstupů">Příklady vstupů a výstupů</a></span></h3>

<p>

<i>Číselné údaje nemusí odpovídat vaší implementaci. Výsledek závisí na způsobu implementace a případné optimalizaci. Optimalizace hodnocena nebude.</i>
</p>

<p>
<pre>$ ./proj2 --tan 1.024 6 10
6 1.642829e+00 1.634327e+00 8.502803e-03 1.642829e+00 3.298801e-09
7 1.642829e+00 1.639216e+00 3.613451e-03 1.642829e+00 1.794520e-11
8 1.642829e+00 1.641294e+00 1.535615e-03 1.642829e+00 7.460699e-14
9 1.642829e+00 1.642177e+00 6.525932e-04 1.642829e+00 4.440892e-16
10 1.642829e+00 1.642552e+00 2.773337e-04 1.642829e+00 0.000000e+00</pre>

</p>

<p>
<pre>$ ./proj2 -m 0.3 0.9
4.8490922156e+00
7.6106234032e+00</pre>

</p>

<p>
<pre>$ ./proj2 -c 1.7 -m 0.15 1.3
1.1248205560e+01
4.2217188781e+01</pre>

</p>

<h2><span><a name="Hodnocení">Hodnocení</a></span></h2>

<p>

Na výsledném hodnocení mají hlavní vliv následující faktory:
</p>

<ul>
<li class="level1">implementace algoritmických schemat pro iterační výpočty,</li>
<li class="level1">volba funkcí a jejich parametrů pro výpočet měřených veličin,</li>
<li class="level1">výpočet tangens a porovnání přesnosti,</li>
<li class="level1">výpočet vzdálenosti a výšky,</li>
<li class="level1">ošetření neočekávaných stavů.</li>
</ul>
