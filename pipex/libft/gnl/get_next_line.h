/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:50:32 by sydauria          #+#    #+#             */
/*   Updated: 2022/08/26 07:33:35 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 42

# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

char	*stop_condition(int fd, size_t nb, char *valid_line, char **buffer);
char	*extract_str(char *buffer, ssize_t *new_line);
char	*get_remainder(ssize_t *problem, ssize_t *exit_loop, char *buffer);
char	*ft_strjoin_and_free(char *actual_line, char *temp);
ssize_t	create_and_fill_buffer(int fd, char **buffer);

#endif
