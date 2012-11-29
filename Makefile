include conf.mk

CC ?= gcc
BUILDDIR ?= .build
CFLAGS ?= $(CFLAGS_$(MODE))

ifeq ($(MAKECMDGOALS),)
	MAKECMDGOALS = $(BINS)
endif

all: $(BINS)

# Génère les dépendance et la compilation d'un fichier source
define COMP_template
  OBJ = $$(subst $$(suffix $(1)),.o,./$$(BUILDDIR)/$(1))
  DEP = $$(OBJ:.o=.d)

  $$(OBJ): $(1)
	@$(CC) -o $$@ -c $(1) $(CFLAGS)

  $$(DEP): $(1)
	@echo -n "$$(dir $$@)" > $$@
	@if ! $(CC) -MM $(1) 2> /dev/null >> $$@; then > $$@; fi;
endef

# Génère la compilation d'un binaire
define BIN_template
  SRCS := $$(wildcard $$(SRCS_$(1)))
  ALL_SRCS  := $$(ALL_SRCS) $$(SRCS)
  OBJS_$(1) := $$(subst $$(suffix $$(firstword $$(SRCS))),.o,$$(addprefix ./$$(BUILDDIR)/,$$(SRCS)))
  DEPS_$(1) := $$(OBJS_$(1):.o=.d)

  $(1): $$(OBJS_$(1))
	@$(CC) $$(filter %.o,$$^) $$(LDFLAGS_$(1)) -o $$@

  ifeq ($$(filter $(1), $(MAKECMDGOALS)),$(1))
    $$(shell mkdir -p $$(sort $$(dir $$(OBJS_$(1)))))
    -include $$(DEPS_$(1))
  else
    clean_$(1):
	@rm -f $$(OBJS_$(1)) $$(DEPS_$(1))
	@rm -f $(1)
    ALL_CLEANS += clean_$(1)
  endif
endef

$(foreach b,$(BINS),$(eval $(call BIN_template,$(b))))
$(foreach s,$(sort $(ALL_SRCS)),$(eval $(call COMP_template,$(s))))
.PHONY: all clean $(ALL_CLEANS)
clean: $(ALL_CLEANS)
	$(foreach d,$(sort $(dir $(addprefix $(BUILDDIR)/,$(ALL_SRCS)))),$(shell rmdir -p $(d) 2> /dev/null))

