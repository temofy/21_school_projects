all:
	@make -C ./libft/
	@make -C ./Assembler/libft/
	@make -C ./Assembler/
	@make -C ./VM/

clean:
	@make -C ./libft/ clean
	@make -C ./Assembler/libft clean
	@make -C ./Assembler/ clean

fclean:
	@make -C ./libft/ fclean
	@make -C ./Assembler/libft fclean
	@make -C ./VM/ fclean
	@make -C ./Assembler/ fclean

new:
	@make -C ./VM/ re
	@make -C ./Assembler/ re

debug:
	@make -C ./VM/ debug

re: fclean all
