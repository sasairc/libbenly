#
#    Makefile for libbenly
#

VERSION      = 1
PATCHLEVEL   = 0
SUBLEVEL     = 0
EXTRAVERSION =
VERSIONSTR   = $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)
LIBS         = `pkg-config --cflags --libs glib-2.0` 
LOCALE       =

OBJS         = libbenly_cmd.so            \
	       libbenly_env.so            \
	       libbenly_file.so           \
	       libbenly_memory.so	  \
	       libbenly_signal.so         \
	       libbenly_string.so

DEFCFLAGS    =	-fPIC			  \
		-DLOCALE=\"$(LOCALE)\"    \
	    	$(LIBS)
DEFLDFLAGS   = -shared			  \
		-Wl,-soname=$@.$(VERSION) \
		$(LIBS)	

all: $(OBJS)

libbenly_cmd.so: cmd.c cmd.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      cmd.o"
	@$(CC) $(CFLAGS) -c $< -o cmd.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) cmd.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o cmd.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) cmd.o -o $@ $(DEFLDFLAGS)
endif

libbenly_env.so: env.c env.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      env.o"
	@$(CC) $(CFLAGS) -c $< -o env.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) env.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o env.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) env.o -o $@ $(DEFLDFLAGS)
endif

libbenly_file.so: file.c file.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      file.o"
	@$(CC) $(CFLAGS) -c $< -o file.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) file.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o file.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) file.o -o $@ $(DEFLDFLAGS)
endif

libbenly_memory.so: memory.c memory.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      memory.o"
	@$(CC) $(CFLAGS) -c $< -o memory.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) memory.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o memory.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) memory.o -o $@ $(DEFLDFLAGS)
endif

libbenly_signal.so: signal.c signal.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      signal.o"
	@$(CC) $(CFLAGS) -c $< -o signal.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) signal.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o signal.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) signal.o -o $@ $(DEFLDFLAGS)
endif

libbenly_string.so: string.c string.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      string.o"
	@$(CC) $(CFLAGS) -c $< -o string.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) string.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o string.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) string.o -o $@ $(DEFLDFLAGS)
endif

install-lib: $(OBJS)
	install -pd $(LIBDIR)
	install -pm 755 libbenly_cmd.so $(LIBDIR)/libbenly_cmd.so.$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_cmd.so.$(VERSIONSTR) $(LIBDIR)/libbenly_cmd.so.$(VERSION)
	ln -sf $(LIBDIR)/libbenly_cmd.so.$(VERSIONSTR) $(LIBDIR)/libbenly_cmd.so
	install -pm 755 libbenly_env.so $(LIBDIR)/libbenly_env.so.$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_env.so.$(VERSIONSTR) $(LIBDIR)/libbenly_env.so.$(VERSION)
	ln -sf $(LIBDIR)/libbenly_env.so.$(VERSIONSTR) $(LIBDIR)/libbenly_env.so
	install -pm 755 libbenly_file.so $(LIBDIR)/libbenly_file.so.$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_file.so.$(VERSIONSTR) $(LIBDIR)/libbenly_file.so.$(VERSION)
	ln -sf $(LIBDIR)/libbenly_file.so.$(VERSIONSTR) $(LIBDIR)/libbenly_file.so
	install -pm 755 libbenly_memory.so $(LIBDIR)/libbenly_memory.so.$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_memory.so.$(VERSIONSTR) $(LIBDIR)/libbenly_memory.so.$(VERSION)
	ln -sf $(LIBDIR)/libbenly_memory.so.$(VERSIONSTR) $(LIBDIR)/libbenly_memory.so
	install -pm 755 libbenly_signal.so $(LIBDIR)/libbenly_signal.so.$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_signal.so.$(VERSIONSTR) $(LIBDIR)/libbenly_signal.so.$(VERSION)
	ln -sf $(LIBDIR)/libbenly_signal.so.$(VERSIONSTR) $(LIBDIR)/libbenly_signal.so
	install -pm 755 libbenly_string.so $(LIBDIR)/libbenly_string.so.$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_string.so.$(VERSIONSTR) $(LIBDIR)/libbenly_string.so.$(VERSION)
	ln -sf $(LIBDIR)/libbenly_string.so.$(VERSIONSTR) $(LIBDIR)/libbenly_string.so

install-header:
	install -pd $(INCLUDEDIR)/benly
	install -pm 644 *.h $(INCLUDEDIR)/benly/

clean:
	-$(RM) -f *.o
	-$(RM) -f $(OBJS)

.PHONY: all		\
	install-lib	\
	install-header	\
	clean
