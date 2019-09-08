/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 09:52:19 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/23 13:16:21 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>

int			visual(t_lemin *data)
{
	data->running = SDL_TRUE;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s"
				, SDL_GetError());
		return (1);
	}
	if (!(data->window = SDL_CreateWindow("Wolfenstein", SDL_WINDOWPOS_CENTERED
					, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT
					, SDL_WINDOW_FULLSCREEN)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s"
				, SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	if (!(data->renderer = SDL_CreateRenderer(data->window, -1
					, SDL_RENDERER_PRESENTVSYNC)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't create renderer: %s", SDL_GetError());
		return (leave_sdl_and_program(data, 1));
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return ();
}
