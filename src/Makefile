#
#    Makefile for libbenly
#

VERSION      = 1
PATCHLEVEL   = 0
SUBLEVEL     = 0
EXTRAVERSION =
VERSIONSTR   = $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)
LOCALE       =
ifeq ($(shell uname), Linux)
SUFFIX       = so
# for Linux
endif
ifeq ($(shell uname), Darwin)
SUFFIX       = dylib
# for Darwin
endif
ifndef SUFFIX
SUFFIX       = so
# for Other System
endif
OBJS         = libbenly_cmd.$(SUFFIX)     \
	       libbenly_column.$(SUFFIX)  \
               libbenly_env.$(SUFFIX)     \
               libbenly_file.$(SUFFIX)    \
               libbenly_hash.$(SUFFIX)    \
               libbenly_memory.$(SUFFIX)  \
               libbenly_proc.$(SUFFIX)    \
               libbenly_signal.$(SUFFIX)  \
	       libbenly_spinner.$(SUFFIX) \
               libbenly_string.$(SUFFIX)  \
               libbenly_typestring.$(SUFFIX)  \
               libbenly_uri.$(SUFFIX)
DEFCFLAGS    = -fPIC                     \
               -DLOCALE=\"$(LOCALE)\"
ifeq ($(shell uname), Linux)
DEFLDFLAGS   = -shared                   \
               -Wl,-soname=$@.$(VERSION)
# for Linux
endif
ifeq ($(shell uname), Darwin)
DEFLDFLAGS   = -dynamiclib -undefined suppress -flat_namespace	\
               -install_name $@ -current_version $(VERSIONSTR)	\
	       -compatibility_version $(VERSION).$(PATCHLEVEL)
# for Darwin
endif
# use GNU Extensions
ifeq ($(WITH_GNU), 1)
DEFCFLAGS    += -D_GNU_SOURCE -D__USE_GNU
endif
# with glib-2.0
ifeq ($(WITH_GLIB), 1)
DEFCFLAGS    += -DWITH_GLIB `pkg-config --cflags glib-2.0`
DEFLDFLAGS   += `pkg-config --libs glib-2.0` 
endif
# with POSIX regex.h
ifeq ($(WITH_REGEX), 1)
DEFCFLAGS    += -DWITH_REGEX
endif
# displaying system call errors
ifdef  LIBRARY_VERBOSE
DEFCFLAGS    += -DLIBRARY_VERBOSE
endif

all: $(OBJS)

libbenly_cmd.$(SUFFIX): cmd.c cmd.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      cmd.o"
	@$(CC) $(CFLAGS) -c $< -o cmd.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) cmd.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o cmd.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) cmd.o -o $@ $(DEFLDFLAGS)
endif

libbenly_column.$(SUFFIX): column.c column.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      column.o"
	@$(CC) $(CFLAGS) -c $< -o column.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) column.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o column.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) column.o -o $@ $(DEFLDFLAGS)
endif

libbenly_env.$(SUFFIX): env.c env.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      env.o"
	@$(CC) $(CFLAGS) -c $< -o env.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) env.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o env.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) env.o -o $@ $(DEFLDFLAGS)
endif

libbenly_file.$(SUFFIX): file.c file.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      file.o"
	@$(CC) $(CFLAGS) -c $< -o file.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) file.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o file.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) file.o -o $@ $(DEFLDFLAGS)
endif

libbenly_hash.$(SUFFIX): hash.c hash.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      hash.o"
	@$(CC) $(CFLAGS) -c $< -o hash.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) hash.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o hash.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) hash.o -o $@ $(DEFLDFLAGS)
endif

libbenly_memory.$(SUFFIX): memory.c memory.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      memory.o"
	@$(CC) $(CFLAGS) -c $< -o memory.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) memory.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o memory.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) memory.o -o $@ $(DEFLDFLAGS)
endif

libbenly_proc.$(SUFFIX): proc.c proc.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      proc.o"
	@$(CC) $(CFLAGS) -c $< -o proc.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) proc.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o proc.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) proc.o -o $@ $(DEFLDFLAGS)
endif

libbenly_signal.$(SUFFIX): signal.c signal.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      signal.o"
	@$(CC) $(CFLAGS) -c $< -o signal.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) signal.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o signal.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) signal.o -o $@ $(DEFLDFLAGS)
endif

libbenly_spinner.$(SUFFIX): spinner.c spinner.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      spinner.o"
	@$(CC) $(CFLAGS) -c $< -o spinner.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) spinner.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o spinner.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) spinner.o -o $@ $(DEFLDFLAGS)
endif

libbenly_string.$(SUFFIX): string.c string.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      string.o"
	@$(CC) $(CFLAGS) -c $< -o string.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) string.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o string.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) string.o -o $@ $(DEFLDFLAGS)
endif

libbenly_typestring.$(SUFFIX): typestring.c typestring.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      typestring.o"
	@$(CC) $(CFLAGS) -c $< -o typestring.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) typestring.o -o $@ $(DEFLDFLAGS) -lcrypt
else
	$(CC) $(CFLAGS) -c $< -o typestring.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) typestring.o -o $@ $(DEFLDFLAGS) -lcrypt
endif

libbenly_uri.$(SUFFIX): uri.c uri.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      uri.o"
	@$(CC) $(CFLAGS) -Wno-format -c $< -o uri.o $(DEFCFLAGS)
	@echo "  CCLD    $@"
	@$(CC) $(LDFLAGS) uri.o -o $@ $(DEFLDFLAGS)
else
	$(CC) $(CFLAGS) -Wno-format -c $< -o uri.o $(DEFCFLAGS)
	$(CC) $(LDFLAGS) uri.o -o $@ $(DEFLDFLAGS)
endif


install-lib: $(OBJS)
	install -pd $(LIBDIR)
	install -pm 755 libbenly_cmd.$(SUFFIX) $(LIBDIR)/libbenly_cmd.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_cmd.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_cmd.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_cmd.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_cmd.$(SUFFIX)
	install -pm 755 libbenly_column.$(SUFFIX) $(LIBDIR)/libbenly_column.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_column.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_column.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_column.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_column.$(SUFFIX)
	install -pm 755 libbenly_env.$(SUFFIX) $(LIBDIR)/libbenly_env.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_env.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_env.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_env.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_env.$(SUFFIX)
	install -pm 755 libbenly_file.$(SUFFIX) $(LIBDIR)/libbenly_file.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_file.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_file.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_file.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_file.$(SUFFIX)
	install -pm 755 libbenly_hash.$(SUFFIX) $(LIBDIR)/libbenly_hash.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_hash.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_hash.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_hash.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_hash.$(SUFFIX)
	install -pm 755 libbenly_memory.$(SUFFIX) $(LIBDIR)/libbenly_memory.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_memory.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_memory.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_memory.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_memory.$(SUFFIX)
	install -pm 755 libbenly_proc.$(SUFFIX) $(LIBDIR)/libbenly_proc.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_proc.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_proc.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_proc.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_proc.$(SUFFIX)
	install -pm 755 libbenly_signal.$(SUFFIX) $(LIBDIR)/libbenly_signal.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_signal.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_signal.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_signal.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_signal.$(SUFFIX)
	install -pm 755 libbenly_spinner.$(SUFFIX) $(LIBDIR)/libbenly_spinner.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_spinner.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_spinner.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_spinner.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_spinner.$(SUFFIX)
	install -pm 755 libbenly_string.$(SUFFIX) $(LIBDIR)/libbenly_string.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_string.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_string.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_string.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_string.$(SUFFIX)
	install -pm 755 libbenly_typestring.$(SUFFIX) $(LIBDIR)/libbenly_typestring.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_typestring.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_typestring.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_typestring.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_typestring.$(SUFFIX)
	install -pm 755 libbenly_uri.$(SUFFIX) $(LIBDIR)/libbenly_uri.$(SUFFIX).$(VERSIONSTR)
	ln -sf $(LIBDIR)/libbenly_uri.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_uri.$(SUFFIX).$(VERSION)
	ln -sf $(LIBDIR)/libbenly_uri.$(SUFFIX).$(VERSIONSTR) $(LIBDIR)/libbenly_uri.$(SUFFIX)

ifeq ($(shell uname), Darwin)
	install_name_tool -change "libbenly_cmd.dylib" "$(LIBDIR)/libbenly_cmd.dylib" $(LIBDIR)/libbenly_cmd.dylib
	install_name_tool -change "libbenly_column.dylib" "$(LIBDIR)/libbenly_column.dylib" $(LIBDIR)/libbenly_column.dylib
	install_name_tool -change "libbenly_env.dylib" "$(LIBDIR)/libbenly_env.dylib" $(LIBDIR)/libbenly_env.dylib
	install_name_tool -change "libbenly_file.dylib" "$(LIBDIR)/libbenly_file.dylib" $(LIBDIR)/libbenly_file.dylib
	install_name_tool -change "libbenly_hash.dylib" "$(LIBDIR)/libbenly_hash.dylib" $(LIBDIR)/libbenly_hash.dylib
	install_name_tool -change "libbenly_memory.dylib" "$(LIBDIR)/libbenly_memory.dylib" $(LIBDIR)/libbenly_memory.dylib
	install_name_tool -change "libbenly_proc.dylib" "$(LIBDIR)/libbenly_proc.dylib" $(LIBDIR)/libbenly_proc.dylib
	install_name_tool -change "libbenly_signal.dylib" "$(LIBDIR)/libbenly_signal.dylib" $(LIBDIR)/libbenly_signal.dylib
	install_name_tool -change "libbenly_spinner.dylib" "$(LIBDIR)/libbenly_spinner.dylib" $(LIBDIR)/libbenly_spinner.dylib
	install_name_tool -change "libbenly_string.dylib" "$(LIBDIR)/libbenly_string.dylib" $(LIBDIR)/libbenly_string.dylib
	install_name_tool -change "libbenly_typestring.dylib" "$(LIBDIR)/libbenly_typestring.dylib" $(LIBDIR)/libbenly_typestring.dylib
	install_name_tool -change "libbenly_uri.dylib" "$(LIBDIR)/libbenly_uri.dylib" $(LIBDIR)/libbenly_uri.dylib
# for Darwin
endif

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
