/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:16:03 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/13 20:20:28 by gabodinho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"

double	*vector(double a, double b, double c);
double	*point(double a, double b, double c);
void	normalize(double tuple[4]);
double	dot_product(double *v1, double *v2);
double	*cross_product(double *v1, double *v2);
double	*identity_matrix(int size);
void	transpose(double *m, int size);
double	*submatrix(double *m, int size, int row, int col);
double	det2x2(double *m);

#endif
