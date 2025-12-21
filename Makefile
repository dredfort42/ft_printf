# ============================================================================
#                         ft_printf Project Makefile
# ============================================================================
# This Makefile builds the ft_printf static library including libft.
# Structure follows best practices: variables first, then phony declarations,
# then targets ordered by importance (all, build, clean, utilities).
# ============================================================================

# ============================================================================
#                           1. PROJECT SETTINGS
# ============================================================================

# Name of the final static library
NAME        := libftprintf.a

# Directory containing libft library
LIBFT_DIR   := libft

# Path to libft archive
LIBFT_A     := $(LIBFT_DIR)/libft.a

# ============================================================================
#                           2. SOURCE FILES
# ============================================================================

# ft_printf source files
SRCS        := ft_printf.c \
               ft_parsing.c \
               ft_handle_percent_conversion.c \
               ft_handle_char_conversion.c \
               ft_handle_string_conversion.c \
               ft_handle_pointer_conversion.c \
               ft_handle_signed_integer_conversion.c \
               ft_handle_unsigned_integer_conversion.c \
               ft_handle_hex_conversion.c \
               ft_process_utils.c
# 			   \
# 			   ft_handle_char.c \
# 			   ft_handle_string.c \
# 			   ft_handle_percent.c \
# 			   ft_handle_integer.c \
# 			   ft_handle_unsigned.c \
# 			   ft_handle_hex.c \
# 			   ft_handle_pointer.c \
# 			   ft_utils.c \
# 			   ft_utils_2.c

# libft source files
LIBFT_SRCS  := $(LIBFT_DIR)/ft_atoi.c \
               $(LIBFT_DIR)/ft_bzero.c \
               $(LIBFT_DIR)/ft_calloc.c \
               $(LIBFT_DIR)/ft_digcount.c \
               $(LIBFT_DIR)/ft_isalnum.c \
               $(LIBFT_DIR)/ft_isalpha.c \
               $(LIBFT_DIR)/ft_isascii.c \
               $(LIBFT_DIR)/ft_isdigit.c \
               $(LIBFT_DIR)/ft_islower.c \
               $(LIBFT_DIR)/ft_isprint.c \
               $(LIBFT_DIR)/ft_isspace.c \
               $(LIBFT_DIR)/ft_isupper.c \
               $(LIBFT_DIR)/ft_itoa.c \
               $(LIBFT_DIR)/ft_lstadd_back.c \
               $(LIBFT_DIR)/ft_lstadd_front.c \
               $(LIBFT_DIR)/ft_lstclear.c \
               $(LIBFT_DIR)/ft_lstdelone.c \
               $(LIBFT_DIR)/ft_lstiter.c \
               $(LIBFT_DIR)/ft_lstlast.c \
               $(LIBFT_DIR)/ft_lstmap.c \
               $(LIBFT_DIR)/ft_lstnew.c \
               $(LIBFT_DIR)/ft_lstsize.c \
               $(LIBFT_DIR)/ft_memchr.c \
               $(LIBFT_DIR)/ft_memcmp.c \
               $(LIBFT_DIR)/ft_memcpy.c \
               $(LIBFT_DIR)/ft_memmove.c \
               $(LIBFT_DIR)/ft_memset.c \
               $(LIBFT_DIR)/ft_putchar_fd.c \
               $(LIBFT_DIR)/ft_putendl_fd.c \
               $(LIBFT_DIR)/ft_putnbr_fd.c \
               $(LIBFT_DIR)/ft_putstr_fd.c \
               $(LIBFT_DIR)/ft_split.c \
               $(LIBFT_DIR)/ft_strchr.c \
               $(LIBFT_DIR)/ft_strdup.c \
               $(LIBFT_DIR)/ft_striteri.c \
               $(LIBFT_DIR)/ft_strjoin.c \
               $(LIBFT_DIR)/ft_strlcat.c \
               $(LIBFT_DIR)/ft_strlcpy.c \
               $(LIBFT_DIR)/ft_strlen.c \
               $(LIBFT_DIR)/ft_strmapi.c \
               $(LIBFT_DIR)/ft_strncmp.c \
               $(LIBFT_DIR)/ft_strnstr.c \
               $(LIBFT_DIR)/ft_strrchr.c \
               $(LIBFT_DIR)/ft_strtrim.c \
               $(LIBFT_DIR)/ft_substr.c \
               $(LIBFT_DIR)/ft_tolower.c \
               $(LIBFT_DIR)/ft_toupper.c

# ============================================================================
#                           3. OBJECT FILES
# ============================================================================

# ft_printf object files
OBJS        := $(SRCS:.c=.o)

# libft object files
LIBFT_OBJS  := $(LIBFT_SRCS:.c=.o)

# ============================================================================
#                           4. COMPILER SETTINGS
# ============================================================================

# Compiler to use
CC          := gcc

# Compiler flags:
# -Wall   : Enable all common warnings
# -Wextra : Enable extra warnings beyond -Wall
# -Werror : Treat all warnings as errors (strict mode)
# -I.     : Add current directory to header search path
CFLAGS      := -Wall -Wextra -Werror -I.

# ============================================================================
#                           5. ARCHIVER SETTINGS
# ============================================================================

# Archive tool for creating static libraries
AR          := ar

# Archiver flags:
# r : Replace or add files to archive
# c : Create archive if it doesn't exist
# s : Write an index (for faster linking)
ARFLAGS     := rcs

# ============================================================================
#                           6. UTILITY COMMANDS
# ============================================================================

# Command to remove files
RM          := rm -f

# ============================================================================
#                           6a. COLOR SETTINGS
# ============================================================================

# ANSI color codes for pretty output
COLOR_RESET   := \033[0m
COLOR_GREEN   := \033[0;32m
COLOR_YELLOW  := \033[0;33m
COLOR_BLUE    := \033[0;34m
COLOR_CYAN    := \033[0;36m
COLOR_RED     := \033[0;31m
COLOR_BOLD    := \033[1m

# ============================================================================
#                           7. PHONY TARGETS
# ============================================================================

# Declare phony targets (not actual files)
.PHONY: all clean fclean re bonus

# Set default target (executed when running 'make' with no arguments)
.DEFAULT_GOAL := all

# ============================================================================
#                           8. BUILD TARGETS
# ============================================================================

# Main target: Build the complete library
# Dependencies: libft must be built first, then ft_printf
all: $(LIBFT_A) $(NAME)

# Build libft library by calling its Makefile
# Uses recursive make to build in the libft directory
$(LIBFT_A):
	@echo "$(COLOR_BLUE)[MAKE] Building libft...$(COLOR_RESET)"
	@ $(MAKE) -C $(LIBFT_DIR)
	@echo "$(COLOR_GREEN)[OK] libft.a ready$(COLOR_RESET)"

# Build the final static library
# Combines ft_printf objects and libft objects into one archive
# $@ = target name ($(NAME))
# $^ = all prerequisites ($(OBJS) $(LIBFT_OBJS))
$(NAME): $(OBJS) $(LIBFT_OBJS)
	@echo "$(COLOR_BLUE)[MAKE] Creating archive $(NAME)...$(COLOR_RESET)"
	@ $(AR) $(ARFLAGS) $@ $^
	@echo "$(COLOR_GREEN)[OK] $(NAME) created successfully$(COLOR_RESET)"

# ============================================================================
#                           9. COMPILATION RULES
# ============================================================================

# Pattern rule: Compile ft_printf .c files to .o files
# $< = first prerequisite (the .c source file)
# $@ = target (the .o object file)
%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

# Pattern rule: Compile libft .c files to .o files in libft/ directory
$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c
	@ $(CC) $(CFLAGS) -c $< -o $@

# ============================================================================
#                           10. CLEANING TARGETS
# ============================================================================

# Remove all object files
# Cleans both ft_printf and libft object files
clean:
	@echo "$(COLOR_BLUE)[MAKE] Removing object files...$(COLOR_RESET)"
	@ $(RM) $(OBJS) $(LIBFT_OBJS)
	@echo "$(COLOR_GREEN)[OK] Object files cleaned$(COLOR_RESET)"

# Remove all generated files (full clean)
# Removes object files and static libraries
fclean: clean
	@echo "$(COLOR_BLUE)[MAKE] Removing libraries...$(COLOR_RESET)"
	@ $(RM) $(NAME) $(LIBFT_A)
	@echo "$(COLOR_GREEN)[OK] All generated files removed$(COLOR_RESET)"

# ============================================================================
#                           11. UTILITY TARGETS
# ============================================================================

# Rebuild everything from scratch
# Equivalent to: make fclean && make all
re: fclean all

# Bonus target (compatibility with 42 projects)
# Can be extended to build bonus features
bonus: all

