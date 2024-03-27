#include "../../include/minishell.h"


int check_single_redirect()
{
	t_token *proc_data;
	char	**cmd_argv;
	int		origin_io[2];
	int		cmd_count;

	cmd_argv = make_tok2D();
	cmd_count = ft_matrixlen(cmd_argv);
	//cmd_argv = make_tok2D();
	proc_data = g_glob.tok;
	// 해당 들어온 값이 1개이여야하고
	if (cmd_count == 1)
	{
		// builtin 값이 0이어야 한다.
		if (!is_builtin(cmd_argv[0]))
		{
			save_origin_io(origin_io);
			if (do_redirect(proc_data))
				g_glob.exit_stat = 1;
			restore_origin_io(origin_io);
			// 해당 부분 개별 요소 free를 안해줌
			free(cmd_argv);
			return (1);
		}
	}
	// 해당 부분 개별 요소 free를 안해줌
	free(cmd_argv);
	return (0);
}
