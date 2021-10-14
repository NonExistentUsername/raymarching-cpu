// Author:
// Title:

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

const float pi = 3.14159265359;

const float radius = 1.;

vec3 light_position = vec3(5, -20, 0);

const vec3 sky_color = vec3(0.0, 1.0, 1.0);
const float angle = 50.;

struct material {
	vec3 color;
    
    float reflection;
    float absorption;
};

struct sphere {
    vec3 point;
    float radius;
    
    material mat;
};

struct cube {
    vec3 point;
    float size;
};

float get_len(vec3 point, sphere sp) {
    return length(sp.point - point) - sp.radius;
}

float get_len(vec3 point, cube cb) {
    return 1.;
}

vec3 get_normal(vec3 point, const in sphere object) {
    const float delta = 0.01;
    
    float dist = get_len(point, object);
    vec3 normal;
    point.x -= delta;
    normal.x = dist - get_len(point, object);
    point.x += delta;

    point.y -= delta;
    normal.y = dist - get_len(point, object);
    point.y += delta;

    point.z -= delta;
    normal.z = dist - get_len(point, object);

    return normalize(normal);
}

sphere sp3 = sphere(vec3(13, 1.2, -1), 0.5, material(vec3(0.990,0.906,0.089), 0., 0.));

const int spheres_size = 4;
sphere spheres[spheres_size];

void init_spheres() {
    spheres[0] = sphere(vec3(14, -0.3, 0), 1., material(vec3(0.830,0.188,0.493), 0.03, 0.));
    spheres[1] = sphere(vec3(17, 1, 2), 2., material(vec3(0.184,1.000,0.737), 0.2, 0.));
    spheres[2] = sphere(vec3(13, 1.2, -1), 0.5, material(vec3(0.990,0.906,0.089), 0.1, 0.));
    spheres[3] = sphere(vec3(14, -2, -4), 3., material(vec3(0.990,0.669,0.301), 0.3, 0.));
}

void init_shapes() {
    init_spheres();
}

float get_cos(const in vec3 a, const in vec3 b) {
    return dot(a, b) / (length(a) * length(b));
}

vec3 calc_color(const in vec3 color, const in vec3 other_color, const in material mat) {
    return color * (1. - mat.reflection - mat.absorption) + other_color * (mat.reflection);
}

float update_len(const in vec3 point, float len) {
    for(int i = 0; i < spheres_size; i++)
        len = min(len, get_len(point, spheres[i]));
    // len = min(len, get_len(point, sp));

    return len;
}

const int steps = 100;
const int max_rec_cnt = 3;

const float min_len = 0.001;
const float max_len = 1000.;
const float default_len = 100.;

vec3 find_point(vec3 point, const vec3 ray) {
    for(int i = 0; i < steps; i++) {
        
        float len = update_len(point, default_len);

        point += ray * len;
        if(abs(len) > max_len|| abs(len) < min_len) break;
    }

    return point;
}

vec3 find_normal(const in vec3 point) {
    for(int i = 0; i < spheres_size; i++)
        if(get_len(point, spheres[i]) < min_len)
            return get_normal(point, spheres[i]);

    return vec3(0, 0, 0);
}

material find_material(const in vec3 point) {
    for(int i = 0; i < spheres_size; i++)
        if(get_len(point, spheres[i]) < min_len)
            return spheres[i].mat;
    
    return material(sky_color, 0., 1.);
}

material combine(material first, material second) {
 	first.color = first.color + second.color * (first.reflection) * (1. - second.reflection);
    first.reflection *= second.reflection;

    return first;
}

vec3 process_ray(vec3 ray) {
    material my_mat = material(vec3(0), 1., 1.);
    
    vec3 point = vec3(0);
    bool used_angle = false;
    float angle = 1.;
    for(int rec_step = 0; rec_step < max_rec_cnt; rec_step++) {
        point = find_point(point, ray);

        material mat = find_material(point);
        my_mat = combine(my_mat, mat);
        
        vec3 normal = find_normal(point);
        // if(!used_angle) {
        //     used_angle = true;
            // angle = get_cos(normalize(light_position - point), normal);
        // }
        
        vec3 new_ray = normalize(2. * (normal + ray) + normal);
        ray = new_ray;
        // return abs(new_ray);
        
        point += 2. * min_len * ray;
    }
    // color = calc_color(color, other_color, mat);
    my_mat.color /= (1. - my_mat.reflection);
    

    return my_mat.color;
	return my_mat.reflection * vec3(1);
}

vec2 rotate(vec2 vec, float angle) {
    float new_x = vec.x * cos(angle) - vec.y * sin(angle);
    float new_y = vec.x * sin(angle) + vec.y * cos(angle);
    
    return vec2(new_x, new_y);
}

vec3 rotateX(vec3 vec, float angle) {
    vec.xz = rotate(vec.xz, angle);
    return vec;
}

vec3 rotateY(vec3 vec, float angle) {
    vec.xy = rotate(vec.xy, angle);
    return vec;
}

float toRadian(float angle) {
    return (pi * angle) / 180.;
}

vec3 generate_ray() {
	vec3 ray = vec3(1, 0, 0);
    
    float anglex = angle / 2.;
    float angley = anglex * u_resolution.x/u_resolution.y;
    
    vec2 position = gl_FragCoord.xy / u_resolution.xy;

	float my_anglex = anglex * (0.5 - position.x);
    float my_angley = angley * (0.5 - position.y);
    
    ray = rotateX(ray, toRadian(my_anglex));
    ray = rotateY(ray, toRadian(my_angley));
    
    return normalize(ray);
}

vec3 tonemapFilmic(vec3 x) {
  vec3 X = max(vec3(0.0), x - 0.004);
  vec3 result = (X * (6.2 * X + 0.5)) / (X * (6.2 * X + 1.7) + 0.06);
  return pow(result, vec3(2.2));
}

void main() {
	init_shapes();
    
    vec3 ray = generate_ray();
    
    vec3 color = process_ray(ray);
    // color = tonemapFilmic(color);
    
    gl_FragColor = vec4(color, 1.0);
}