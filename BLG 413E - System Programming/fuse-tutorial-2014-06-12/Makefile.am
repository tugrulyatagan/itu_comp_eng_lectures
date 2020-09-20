SUBDIRS = example html src

EXTRA_DIST = autogen.sh index.html

# these are overrides for a bunch of targets I don't want to be created
install install-data install-exec uninstall installdirs check installcheck:
	echo this tutorial is not intended to be installed

install-dvi install-html install-info install-ps install-pdf dvi pdf ps info html:
	echo this tutorial's documentation is intended to be accessed from within the tutorial
