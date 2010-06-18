DOC=PF

all: dvi bib.aux
	dvipdf $(DOC).dvi

dvi: $(DOC).tex
	latex $(DOC)
	bibtex $(DOC)
	pslatex $(DOC)

bib.aux: $(DOC).bib
	bibtex $(DOC)

clean:
	rm -f $(DOC).aux $(DOC).log $(DOC).ps $(DOC).dvi $(DOC).pdf $(DOC).toc $(DOC).lo* $(DOC).bbl $(DOC).blg


