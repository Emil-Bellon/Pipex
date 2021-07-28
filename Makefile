## TARGET_TYPE
TARGET_EXE	= pipex
TARGET_LIB	= lib.a

## PROJECT NAME (Choose target)
NAME	= $(TARGET_EXE)

## SRCS
SRC_DIR=Sources

SRCS=main2.c pipex_utils.c pipex_utils2.c

## HEADER FILES
HEADER_FILES=pipex.h

## HEADERS
HEADERS = Headers/

## BINS
BIN_DIR = bin
OBJS	= $(addprefix $(BIN_DIR)/, $(SRCS:.c=.o))

## LIBS
LIB				= Library
## Make sure that libft is in $(LIB) and that it outputs libft.a
LIB_HEADER		= libft/
LOCAL_LIB_DIRS		= libft
## Use this to add external libs to your project (ex: libm)
## !! You have to use the "lib" prefix anyway !! 
EXTERN_LIBS		= 

## GCC
CC			= gcc -c
GCC			= gcc
OUT			= --output
CFLAGS		= -Werror -Wextra -Wall # -g3 -fsanitize=address

##
##			---- COLORS ----
##


#							--> Regular Colors
BLACK=		\033[0;30m
RED=		\033[0;31m
GREEN=		\033[0;32m
YELLOW=		\033[0;33m
BLUE=		\033[0;34m
PURPLE=		\033[0;35m
CYAN=		\033[0;36m
WHITE=		\033[0;37m

#							--> Bold
BBLACK=		\033[1;30m
BRED=		\033[1;31m
BGREEN=		\033[1;32m
BYELLOW=	\033[1;33m
BBLUE=		\033[1;34m
BPURPLE=	\033[1;35m
BCYAN=		\033[1;36m
BWHITE=		\033[1;37m



##
##			---- RULES ----
##



## Require NAME and prints descritpion(42 norm)
all: desc libs $(TARGET_EXE)
	@echo "$(BWHITE)[$(BBLUE)$(NAME)$(BWHITE)] \033[0mDone."


## Prints a short description of what is compiling.
desc :
	@printf "$(BPURPLE)>>> Making target $(CYAN)"
	@if [ $(NAME) = $(TARGET_EXE) ] ; then \
		printf "exe $(BPURPLE)-> '$(NAME)'\n$(WHITE)" ; \
	else \
		printf "lib $(BPURPLE)-> '$(NAME)'\n$(WHITE)" ; \
	fi



## EXE
## Require all .a
## Require bin dir and objs
## Require headers
## -> Links the objs with libs.
$(TARGET_EXE) : $(BIN_DIR) $(OBJS) $(HEADER_FILES:%=$(HEADERS)%)
	@echo "$(BWHITE)[$(BBLUE)$(NAME)$(BWHITE)] $(BGREEN)Linked program $(CYAN)'$(NAME)'$(WHITE)."
	@$(GCC) $(OUT) $(TARGET_EXE) $(CFLAGS) $(LOCAL_LIB_DIRS:%=-L$(LIB)/%) $(OBJS) $(LOCAL_LIB_DIRS:lib%=-l%) $(EXERN_LIBS:lib%=-l%) $(FRAMEWORKS)



## LIB
## Require all .a
## Require bin dir and objs
## Require headers
## -> Links the objs with libs.
$(TARGET_LIB) : $(foreach D, $(LOCAL_LIB_DIRS), $(LIB)/$D/$D.a) $(BIN_DIR) $(OBJS) $(HEADERS)
	@echo "$(BWHITE)[$(BBLUE)$(NAME)$(BWHITE)] $(BGREEN)Linked library $(CYAN)'$(NAME)'$(WHITE)."
	@ar rcs $(NAME) $(OBJS) $(foreach D, $(LOCAL_LIB_DIRS), $(LIB)/$D/$D.a)



## Makes the bin dir.
$(BIN_DIR) :
	@echo "$(BYELLOW)Warning : no $(BIN_DIR) found.\ncreating one..."
	@mkdir -p $(BIN_DIR)



## Require a C source
## -> Compiles a c source to a bin o file
$(BIN_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER_FILES:%=$(HEADERS)/%)
	@printf$D "$(BWHITE)[$(BBLUE)$(NAME)$(BWHITE)] $(BWHITE)[$(BGREEN)✔️$(BWHITE)] Compiled : $(BGREEN)$<$(WHITE)\n"
	@mkdir -p $(shell dirname $@)
	@$(CC) $(OUT) $@ $(LIB_HEADER:%=-I$(LIB)/%) $(HEADERS:%=-I%) -I/usr/include $< $(CFLAGS)



## Require libs .a (is they exist ?)
## -> Makes libs.
libs :
	@for lib in $(LOCAL_LIB_DIRS) ; do \
		make -C $(LIB)/$${lib} ; \
	done



## -> Cleans the binarys
clean :
	@echo "$(BRED)Cleaning o files"
	@rm -rf $(BIN_DIR)
	@for lib in $(LOCAL_LIB_DIRS) ; do \
		make -C $(LIB)/$${lib} clean ; \
	done



## Requires clean
## -> Cleans the executable
fclean : clean
	@echo "$(BRED)Cleaning all"
	@rm -rf $(NAME)
	@for lib in $(LOCAL_LIB_DIRS) ; do \
		if [ $${lib} != "libmlx_Linux" ] ; then \
		make -C $(LIB)/$${lib} fclean ; \
		fi \
	done



re : clean fclean all

.PHONY : all re clean fclean libs desc
