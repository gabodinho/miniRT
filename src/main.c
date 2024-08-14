/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabodinho <gabodinho@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:25:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/08/14 21:55:18 by gabodinho        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    print_vec(double *v, int size)
{
    char *str;

	if (!v)
		return;
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
    double *p = point(0.5, 0.5, 0);
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
    // print_vec(id_mat, 4);
    transpose(id_mat, 4);
    print_vec(id_mat, 4);
	// printf("submatrix:\n");
	// double *sub = submatrix(id_mat, 4, 3, 3);
	// print_vec(sub, 3);
    // printf("minor: %f\n", det2x2(submatrix(sub, 3, 0, 2)));
    // double test_mat[16] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    // printf("cofactor: %f\n", cofactor(test_mat, 4, 0, 3));
    // printf("det: %f\n", determinant(test_mat, 3));
    double m2[16] = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
    print_vec(m2, 4);
    // double *m3 = invert(m2, 4);
    // printf("invert: \n");
    // print_vec(m3, 4);
    double *m4 = mat_mat_prod(m2, id_mat, 4);
    print_vec(m4, 4);
    print_vec(mat_vec_prod(m4, v), 0);
    double **r = ray(p, v);
    print_vec(position(r, 2.5), 0);
	printf("last stop\n");
	t_world *w;
	w = malloc(sizeof(t_world));
	t_object *obj;
	obj = malloc(sizeof(t_object));
	obj -> shape = SPHERE;
	w -> objects = &obj;
	w -> n_obj = 1;
	t_intersect *res = intersect_world(w, r);
	printf("intersecti res: %f\n", res -> t);
    return (0);
}