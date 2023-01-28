/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_inout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htoustsi <htoustsi@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:34:24 by htoustsi          #+#    #+#             */
/*   Updated: 2023/01/28 17:18:33 by htoustsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_invalidation(t_cmd *cmd, int *fd, char **infiles)
{
	int i;

    i = 0;	
//    if (infiles && infiles[0])
//    {
//        while (infiles[i])
//            ++i;
//    }
    if (cmd->here_doc)
    {
        *fd = STDIN_FILENO;
        return (1);
    }
    else
    {
        if (access(infiles[i], R_OK) < 0)
			perror("Input file");
		else
		{
//			if (cmd->here_doc == 0)
//            {
            *fd = open(infiles[i], O_RDONLY);
            printf("in-file opened\n");
			if (*fd < 0)
			    perror("Input file");
			else
			    return (1);
//            }
//            else if (infile == 0 || infile == 2)
//                *fd = STDIN_FILENO;
//            return (1);
		}
	}
	return (-1);
}

int ft_outvalidation(t_cmd *cmd, int *fd)
{
    int i;

    i = 0;	
    if (cmd->out && cmd->out[0].name)
    {
        while (cmd->out[i].name)
        ++i;
        if (access(cmd->out[i - 1].name, R_OK) < 0)
        {
            perror("Output file");
            return (-1);
        }
        else
        {
            if (cmd->out[i - 1].num == 0)
		        *fd = open(cmd->out[i - 1].name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            else if (cmd->out[i - 1].num == 1)
                *fd = open(cmd->out[i - 1].name, O_WRONLY | O_CREAT | O_APPEND, 0666);
//            return (1);
        }
    }
    else
        *fd = STDOUT_FILENO;
    return (1);
}

int	ft_parce_cmd(t_cmd *cmd, t_env_list *env_list)
{
	int		fd_in[2];
	int		fd_out[2];
	int		proc;
//    char    **cmd_argv;
//    int     cmd_argc;
//    int     infile;
//    int     outfile;
//    int     i;
//    int     heredoc;

//    cmd_argc = ft_numwords(cmd, '|');
//    cmd_argv = ft_split(cmd, '|');
//    infile = 0;
//    outfile = 0;
//    heredoc = 0;
//    if (ft_numwords(cmd_argv[0], '<') > 1)
//        infile = 1;
//    if (ft_numwords(cmd_argv[cmd_argc - 1], '>') > 1)
//        outfile = 1;
//    if (cmd_argc == 1 && infile == 0 && outfile == 0)
//        ft_cmd_exec(cmd, STDIN_FILENO, STDOUT_FILENO);
//
    if (!(cmd->next))
    {
        if (!cmd->in && !cmd->out && !execute_path(cmd, env_list))
            return (1);
        else
//            return (0);
//    }
//    else
    {
//        while (cmd && cmd->cmd)
//        {
//        cmd_argv = ft_add_outfile(cmd_argv, cmd_argc, &outfile);
//        ++cmd_argc;
//        proc = 0;
//        while (proc < cmd_argc)
//        {
//            printf("%s\n", cmd_argv[proc]);
//            ++proc;
//        }
//        printf("test1\n");
//        cmd_argv = ft_add_infile(cmd_argv, cmd_argc, &infile);
//        ++cmd_argc;
//        if (infile == 2)
//            ++cmd_argc;
//        proc = 0;
//        while (proc < cmd_argc)
//        {
//            cmd_argv[proc] = ft_trim_spaces(cmd_argv[proc], 0, 0);
//            ++proc;
//        }
//    proc = 0;
//    while (proc < cmd_argc)
//    {
//        printf("%s\n", cmd_argv[proc]);
//        ++proc;
//    }
//	        i = 0;
//            while (cmd && cmd->in[i])
//                ++i;
            if (ft_invalidation(cmd, &fd_in[0], cmd->in) < 0)
		        return (0);
//
	        if (cmd->here_doc == 1)// && (cmd_argc >= 5))
	        {
                if (ft_outvalidation(cmd, &fd_out[1]) < 0)
                    return (0);
//                i = 0;	
//                if (cmd->out && cmd->out[0].name)
//                {
//                    while (cmd->out[i].name)
//                    ++i;
//                    if (cmd->out[i - 1].num == 0)
//		                fd_out[1] = open(cmd->out[i - 1].name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
//                    else if (cmd->out[i - 1].num == 1)
//                        fd_out[1] = open(cmd->out[i - 1].name, O_WRONLY | O_CREAT | O_APPEND, 0666);
//                }
//                else
//                    fd_out[1] = STDOUT_FILENO;
                printf("execution\n");
		        pipe(fd_in);
		        proc = fork();
		        if (proc < 0)
			        perror("Forking error");
		        else if (proc == 0)
			        ft_getline_cmd(fd_in, cmd->cmd);
            }
	        else if (cmd->here_doc == 0) //&& (cmd_argc >= 4))
	        {
		        fd_in[1] = 0;
//                if (outfile == 1)
//		            fd_out[1] = open(cmd_argv[cmd_argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//                else if (outfile == 2)
//                    fd_out[1] = open(cmd_argv[cmd_argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
//                else
//                    fd_out[1] = STDOUT_FILENO;
                if (ft_outvalidation(cmd, &fd_out[1]) < 0)
                    return (0);
//                i = 0;	
//                if (cmd->out && cmd->out[0].name)
//                {
//                    while (cmd->out[i].name)
//                    ++i;
//                    if (cmd->out[i - 1].num == 0)
//		                fd_out[1] = open(cmd->out[i - 1].name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
//                    else if (cmd->out[i - 1].num == 1)
//                        fd_out[1] = open(cmd->out[i - 1].name, O_WRONLY | O_CREAT | O_APPEND, 0666);
//                }
//                else
//                    fd_out[1] = STDOUT_FILENO;
	        }
            printf("test\n");
            if (!cmd->next)
                ft_cmd_exec(cmd, fd_in[0], fd_out[1], env_list);
            else
	            ft_pipe(cmd, fd_in, fd_out, env_list);
        }
	        wait(NULL);
            if (fd_out[1] != 1)
	            close(fd_out[1]);
//            cmd = cmd->next;
//        }
    }
	return (1);
}
