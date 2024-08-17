SUBDIRS = 01_basic_module

all: subdirs

all: subdirs

subdirs:
	for n in $(SUBDIRS); do $(MAKE) -C $$n || exit 1; done

clean:
	for n in $(SUBDIRS); do $(MAKE) -C $$n clean; done

test:
	for n in $(SUBDIRS); do $(MAKE) -C $$n test; done