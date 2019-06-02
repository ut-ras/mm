# Quick and dirty Makefile that builds everything so that we have an easy way to
# generate a compile commands DB.

# This doubles as a registry of all the projects we have in this repo.

TEST_PROGRAMS := apa102-test detect-test encoder-test motor-test sensor-test wall-follow mouse-test

PROJECTS := $(addprefix test-programs/,$(TEST_PROGRAMS)) components/hal/examples

# If not specified:
CMD := all

# Colors:
BOLD   := $(shell echo -e '\033[0;1m')
CYAN   := $(shell echo -e '\033[0;36m')
PURPLE := $(shell echo -e '\033[0;35m')
GREEN  := $(shell echo -e '\033[0;32m')
BROWN  := $(shell echo -e '\033[0;33m')
RED    := $(shell echo -e '\033[1;31m')
NC     := $(shell echo -e '\033[0m')

FMT := clang-format
THREADS := $(shell nproc)

.PHONY: compdb
compdb:
	bear $(MAKE) all

.PHONY: count
count:
	@loc

.PHONY: format
format:
	@find . -regextype egrep \
		  -regex ".*\.(c|h|cpp|S){1}" \
		! -path ".*/build/*" \
		  -print0 \
	| xargs -0 -P $(THREADS) clang-format -verbose -i

.PHONY: $(PROJECTS)
$(PROJECTS):
	$(info $(BOLD)Staring $@ ($(CMD))...$(NC))
	@$(MAKE) -C $@ $(CMD) && \
	echo "$(CYAN)$@ ($(CMD)) successful.$(NC)"

.DEFAULT_GOAL = all
.PHONY: all
all: $(PROJECTS)

.DEFAULT = %
.PHONY: %
%:
	$(MAKE) CMD=$@ all
