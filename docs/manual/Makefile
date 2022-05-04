# Use Bash shell expansion
SHELL=/bin/bash
#The program that you use for viewing pdf files
PDFVIEWER = qpdfview
# Change name of this if you change the name of demothesis.tex, should be name of the main tex file
TEXMAINFILE = main.tex
# Name that you would like for your resulting pdf file, without extension.
# Defaults to $(TEXMAINFILE) with .pdf as extension
PDFNAME = $(shell basename -s.tex $(TEXMAINFILE))
#Location of latexmk binary
MKLATEX = latexmk
#Options to latexmk, should need to be changed
MKLATEXOPTS = -pdf -pdflatex="pdflatex -interaction=errorstopmode" -use-make -jobname=$(PDFNAME)
#MKLATEXOPTS = -pdf -pdflatex="pdflatex -interaction=nonstopmode" -use-make -jobname=$(PDFNAME)

FIGURES_DIR = figures
#DOT_FILES = $(wildcard $(FIGURES_DIR)/*.dot)
#FIGURES = $(DOT_FILES:dot=png)
OUT_DIR = aux_dir

.PHONY: all clean view 

all: $(FIGURES) $(PDFNAME).pdf
	cp $(OUT_DIR)/$(PDFNAME).pdf $(PDFNAME).pdf

$(PDFNAME).pdf: $(TEXMAINFILE) *.tex
	$(MKLATEX) -outdir=$(OUT_DIR) $(MKLATEXOPTS) $<

$(FIGURES_DIR)/%.png: $(FIGURES_DIR)/%.dot
	dot -Tpng $< -o $(FIGURES_DIR)/$*.png

view: $(PDFNAME).pdf
	$(PDFVIEWER) $(PDFNAME).pdf &

clean:
	$(MKLATEX) -CA
	rm -f $(PDFNAME).pdf 
	rm -f $(FIGURES)
	rm -f $(OUT_DIR)/*

