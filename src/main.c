/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:25:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/13 20:25:28 by gabodinho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    print_vec(double *v, int size)
{
    char *str;

    if (size)
    {
        for (int i = 0; i < size; i++)
            printf("row %d: %f %f %f %f\n", i, v[i*size], v[size*i+1], v[size*i+2], v[size*i+3]);
        return;
    }
    if (v[3])
        str = "point";
    else
        str = "vector";
    printf("this is a %s: %f, %f, %f\n", str, v[0], v[1], v[2]);
}

int main(void)
{
    int c;
    double *id_mat;

    c = write(1, "hello world\n", 12);
    c++;
    double *v = vector(1, 2, 3);
    double *p = vector(-1, 2, -3);
    print_vec(p, 0);
    print_vec(v, 0);
    // normalize(p);
    // normalize(v);
    // print_vec(p, 0);
    // print_vec(v, 0);
    printf("dot product: %f\n", dot_product(v, p));
    double *v2 = cross_product(p, v);
    print_vec(v2, 0);
    id_mat = identity_matrix(4);
	id_mat[1] = 5;
	id_mat[3] = 15;
	id_mat[6] = 3;
	id_mat[7] = -5;
	id_mat[11] = 1.9;
    print_vec(id_mat, 4);
    transpose(id_mat, 4);
    print_vec(id_mat, 4);
	printf("submatrix:\n");
	double *sub = submatrix(id_mat, 4, 3, 3);
	print_vec(sub, 3);
    return (0);
}