/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:23:21 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 11:42:18 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>

char		*g_dir;
int			g_j;
int			g_point_point;

int			ft_exec_env(char **envi, char ***newargs);
int			ft_exec_cd(char **envi, char **args, int i);
char		*create_path(char **envi, char *args, char *elem);
int			str_is_in(char *str, char *elem);
char		*ft_get_elem(char **envi, char *elem);
char		*ft_replace_case_tab(char *dir, char *elem, char *path_elem);
int			str_is(char *str, char *elem);
int			set_env_var(char *type, char *val, char **envi);
void		print_pwd(char **envi);
void		ft_change_pwd(char *type, char **envi, char *args);
char		*ft_cut_path(char *str, char c);
void		ft_is_slash_dir(char *type, char **envi, char *args);
char		**ft_set_env(char **envi, char *name, char *value, char *overwrite);
char		**ft_realloc (char **envi, int cpt, char *name);
int			ft_check_set_env(char **newargs);
int			run_cmd(char *path, char **args, char **newenv);
static int	check_if_is_binary(char **args, char **envi);
static int	is_executable(char *bin_path, struct stat f, char **ag, char **env);
void		ft_free_str_double_tab(char **tab);
char		*ft_cut_beg_path(char *str, char c);
int			nb_char_in_str(char *str, char c);
char		**ft_unsetenv(char *name, char **envi, char **newargs);
char		**ft_desalloc(char **envi, int cpt, char *name);
char		**ft_strsplit_args(char const *s, char c, char d, char e);
static int	ft_caltab_arg(char const *str, char c, char d, char e);
static int	ft_strlen_tab_arg(char const *str, char c, char d, char e);
int			pos_type(char *type, char **envi);
void		change_path_env(char *path, int print_path, char **env, char **ag);
int			check_if_start_bin(char *str, char **envi);
char		*ft_strjoinch(char const *s1, char c);
int			is_cmd(char *path);
char		**ft_desalloc_first(char **envi, int cpt);
int			nb_case(char **str);
char		**ft_init_env(int ac, char **av, char **envi);
int			echo_built(char **args, char **envi);
int			ft_exit(char **newargs);
char		*str_equal(char *str, int i);
char		**ft_dup_tab_double(char **envi);
char		**create_env(void);
char		**ft_desalloc_case(char **args, int cpt, int cases);
void		ft_print_env(char **envi);
void		print_prompt(char **newenv);
char		**ft_parse_input(char *str, char **newargs);
char		*dofile_path(char *name, char *file_path);
char		**exec_cmd(int cpt, char ***newargs, char **newenv, char **envi);
void		handle_signal2(int sinl);
char		*ft_duplicate_path(char *str, int size_env);
void		print_error(char **newargs, int turn, int env_cmd, int k);
void		print_error_cd(char *path);
void		handle_signal(int signl);
int			ft_is_home(char **envi, char *str1, char *str2);
int			elem_is_in_env(char **envi, char *name);
char		*ft_replace(char *str, char *term, char *replace_by);
char		**is_env_var_set(char **newargs, char **newenv, char **envi, int i);
char		**launch_build(int i, char **newenv, char **newargs, char **envi);
int			exec_cmd_bis(int cpt, char ***newargs, char ***newenv, char **envi);
void		actualise_env(char **newenv, char **envi);
int			get_access(char *tmp);
int			is_tiret(char **args, char **envi, char *path_home);
int			is_tild(char **args, char **envi, char *path_home);
void		ft_change_pwd(char *typ, char **env, char *args);
int			ft_change_pwd_next(char **env, char *tmp2, char *typ, char **tmp);
char		**do_the_split(char **envi, char *tmp, char **path, int *i);
int			attrib_value(int *is_i, int i);
int			exec_cmd_bis(int cpt, char ***newargs, char ***newenv, char **envi);

#endif
