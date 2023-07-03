# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jhendrik <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/09 15:46:48 by jhendrik      #+#    #+#                  #
#    Updated: 2023/07/03 13:56:19 by jhendrik      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Defining directories
SRCDIR := ./src
OBJDIR := ./obj
LIBFTDIR := ./src/libft

SUBDIRS := Processes \
	 Utils \
	 Checks \
	 Creating
SRCDIRS := $(foreach dir,$(SUBDIRS),$(addprefix $(SRCDIR)/,$(dir)))
OBJDIRS := $(foreach dir,$(SUBDIRS),$(addprefix $(OBJDIR)/,$(dir)))

# Defining extentions
SRCEX = .c
OBJEX = .o

# Add the SRCDIRS to VPATH so make knows where to find the srcfiles
VPATH := $(SRCDIRS)

# Define target
NAME := pipex

# Defining files
SRCHEADER := ./src/src.h
LIBFT_HEADER := ./src/libft/libft.h
LIBFT := ./src/libft/libft.a
SRCFILES := Utils/px_free_split.c \
	 Utils/px_am_subs.c \
	 Utils/px_fillptrsubs.c \
	 Utils/px_find_envvar.c \
	 Utils/px_split_xtr.c \
	 Utils/px_splitpaths.c \
	 Utils/px_swapfds.c \
	 Utils/px_valid_cmnpath.c \
	 Utils/px_errors.c \
	 Processes/px_child.c \
	 Processes/px_parent.c \
	 Checks/px_checks.c \
	 Creating/px_mama_children.c \
	 main.c
OBJFILES :=$(addprefix $(OBJDIR)/,$(SRCFILES:$(SRCEX)=$(OBJEX)))

# Defining flags
CFLAGS ?= -Wall -Werror -Wextra

# Prettifying output
# Reset
Reset="\033[0m"			# Text Reset

# Regular Colors
Black="\033[0;30m"			# Black
Red="\033[0;31m"			# Red
Green="\033[0;32m"			# Green
Yellow="\033[0;33m"			# Yellow
Blue="\033[0;34m"			# Blue
Light_Blue="\033[1;34m"		#Light Blue
Purple="\033[0;35m"			# Purple
Cyan="\033[0;36m"			# Cyan
White="\033[0;37m"			# White

# Bold text style
Bold="\033[1m"

all: make_libft $(NAME)

$(NAME): $(OBJFILES)
	@echo $(Light_Blue) Compiling $(NAME) $(Reset)
	@$(CC) $(LIBFT) $(OBJFILES) -o $(NAME)
	@echo $(Green) Succesfully made program $(NAME) $(Reset)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCHEADER) | $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $<
	@mv ./$(notdir $@) $(@D)

make_libft:
	@$(MAKE) bonus -C $(LIBFTDIR)

$(OBJDIR):
	@mkdir $@

clean:
	@rm -f $(OBJFILES)
	@$(MAKE) clean -C $(LIBFTDIR)
	@echo $(Yellow) Files with extension $(OBJEX) are gone $(Reset)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(MAKE) cleandirs
	@echo $(Yellow) The program $(NAME) went missing $(Reset)

cleandirs: | $(OBJDIR)
	@rm -R $(OBJDIR)
	@$(MAKE) cleandirs -C $(LIBFTDIR)
	@echo $(Yellow) Removed $(OBJDIR) $(Reset)

re: fclean all

.PHONY: all, clean, fclean, cleandirs, make_libft, re 

