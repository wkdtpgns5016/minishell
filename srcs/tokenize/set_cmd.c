#include "../../includes/minishell.h"

t_cmds	*new_set_cmds(t_info *info, char *line)
{
	t_cmds	*cmds;
	char	*new_line;
	char	**token;
	char	**temp;

	cmds = 0;
	// readline 문자열 syntax error 체크
	if (check_syntax(info, line, 0))
		return (0);
	// lastpipe 실행
	new_line = add_last_cmd(line, info);
	if (new_line == 0)
		return (0);
	// tokenize
	token = divide_line(new_line);
	// 토큰들 정리
	temp = token;
	token = divide_token_garbage(temp);
	ft_free_arr((char ***)&temp);
	// 파이프 기준으로 분할하여 구조체에 삽입
	cmds = insert_cmds(token, info);
	ft_free_arr((char ***)&token);
	// 환경변수 해석 및 작은 따옴표 제거
	//interpret_cmds(cmds, info);
	return (cmds);
}
