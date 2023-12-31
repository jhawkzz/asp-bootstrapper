# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  FBAlpha_Shock_config = debug

else ifeq ($(config),release)
  FBAlpha_Shock_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := FBAlpha-Shock

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

FBAlpha-Shock:
ifneq (,$(FBAlpha_Shock_config))
	@echo "==== Building FBAlpha-Shock ($(FBAlpha_Shock_config)) ===="
	@${MAKE} --no-print-directory -C . -f FBAlpha-Shock.make config=$(FBAlpha_Shock_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f FBAlpha-Shock.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   FBAlpha-Shock"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"