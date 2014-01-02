/*
 * ml-lib, a machine learning library for Max and Pure Data
 * Copyright (C) 2013 Carnegie Mellon University
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ml.h"

#include <flext.h>

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

#include <stdint.h>

namespace ml
{
    
class ml_svm : ml_base
{
    FLEXT_HEADER_S(ml_svm, ml_base, setup);
    
public:
    ml_svm()
    : nr_fold(2), estimates(false)
    {
        post("ml.svm: Support Vector Machines using the svm library");
        
//        param.svm_type = C_SVC;
//        param.kernel_type = RBF;
//        param.degree = 3;
//        param.gamma = 0;
//        param.coef0 = 0;
//        param.nu = 0.5;
//        param.cache_size = 100;
//        param.C = 1;
//        param.eps = 1e-3;
//        param.p = 0.1;
//        param.shrinking = 1;
//        param.probability = 1;
//        param.nr_weight = 0;
//        param.weight_label = &weight_labels[0];
//        param.weight = &weight_values[0];
//        
//        prob.l = 0;
//        prob.x = NULL;
//        prob.y = NULL;
        
    }
    
    ~ml_svm()
    {
        
    }
    
protected:
    static void setup(t_classid c)
    {        
        FLEXT_CADDATTR_SET(c, "type", set_type);
        FLEXT_CADDATTR_SET(c, "kernel", set_kernel);
        FLEXT_CADDATTR_SET(c, "degree", set_degree);
        FLEXT_CADDATTR_SET(c, "gamma", set_gamma);
        FLEXT_CADDATTR_SET(c, "coef0", set_coef0);
        FLEXT_CADDATTR_SET(c, "cost", set_cost);
        FLEXT_CADDATTR_SET(c, "nu", set_nu);
        FLEXT_CADDATTR_SET(c, "epsilon", set_epsilon);
        FLEXT_CADDATTR_SET(c, "cachesize", set_cachesize);
        FLEXT_CADDATTR_SET(c, "shrinking", set_shrinking);
        FLEXT_CADDATTR_SET(c, "estimates", set_estimates);
        FLEXT_CADDATTR_SET(c, "weights", set_weights);
        FLEXT_CADDATTR_SET(c, "mode", set_mode);
        
        FLEXT_CADDATTR_GET(c, "type", get_type);
        FLEXT_CADDATTR_GET(c, "kernel", get_kernel);
        FLEXT_CADDATTR_GET(c, "degree", get_degree);
        FLEXT_CADDATTR_GET(c, "gamma", get_gamma);
        FLEXT_CADDATTR_GET(c, "coef0", get_coef0);
        FLEXT_CADDATTR_GET(c, "cost", get_cost);
        FLEXT_CADDATTR_GET(c, "nu", get_nu);
        FLEXT_CADDATTR_GET(c, "epsilon", get_epsilon);
        FLEXT_CADDATTR_GET(c, "cachesize", get_cachesize);
        FLEXT_CADDATTR_GET(c, "shrinking", get_shrinking);
        FLEXT_CADDATTR_GET(c, "estimates", get_estimates);
        FLEXT_CADDATTR_GET(c, "weights", get_weights);
        FLEXT_CADDATTR_GET(c, "mode", get_mode);
        
        FLEXT_CADDMETHOD_(c, 0, "cross_validation", cross_validation);
    }
    
    // Methods
    void save(const t_symbol *path) const;
    void load(const t_symbol *path);
    void cross_validation();
    void train();
    void clear();
    void classify(int argc, const t_atom *argv);
    void usage();
    
    // Attribute Setters
    void set_type(int type); // svm type
    void set_kernel(int kernel);
    void set_degree(int degree);
    void set_gamma(float gamma);
    void set_coef0(float coef0);
    void set_cost(float cost);
    void set_nu(float nu);
    void set_epsilon(float epsilon);
    void set_cachesize(int cachesize);
    void set_shrinking(int shrinking);
    void set_estimates(bool estimates);
    void set_weights(const AtomList &weights);
    void set_mode(int mode); // cross validation mode
    
    // Attribute Getters
    void get_type(int &type) const;
    void get_kernel(int &type) const;
    void get_degree(int &type) const;
    void get_gamma(float &gamma) const;
    void get_coef0(float &coef0) const;
    void get_cost(float &cost) const;
    void get_nu(float &nu) const;
    void get_epsilon(float &epsilon) const;
    void get_cachesize(int &cachesize) const;
    void get_shrinking(int &shrinking) const;
    void get_estimates(bool &estimates) const;
    void get_weights(AtomList &weights) const;
    void get_mode(int &mode) const;
    
private:
    // Method wrappers
    FLEXT_CALLBACK(cross_validation);
    
    // Attribute wrappers
    FLEXT_CALLVAR_I(get_type, set_type);
    FLEXT_CALLVAR_I(get_kernel, set_kernel);
    FLEXT_CALLVAR_I(get_degree, set_degree);
    FLEXT_CALLVAR_F(get_gamma, set_gamma);
    FLEXT_CALLVAR_F(get_coef0, set_coef0);
    FLEXT_CALLVAR_F(get_cost, set_cost);
    FLEXT_CALLVAR_F(get_nu, set_nu);
    FLEXT_CALLVAR_F(get_epsilon, set_epsilon);
    FLEXT_CALLVAR_I(get_cachesize, set_cachesize);
    FLEXT_CALLVAR_I(get_shrinking, set_shrinking);
    FLEXT_CALLVAR_B(get_estimates, set_estimates);
    FLEXT_CALLVAR_V(get_weights, set_weights);
    FLEXT_CALLVAR_I(get_mode, set_mode);
    
    // Instance variables
    
    int nr_fold;
    bool estimates;
    
   };

// Utility functions

    
// Attribute setters
void ml_svm::set_type(int type)
{
    switch (type)
    {
        case GRT::C_SVC:
        case GRT::NU_SVC:
        case GRT::ONE_CLASS:
        case GRT::EPSILON_SVR:
        case GRT::NU_SVR:
//            param.svm_type = type;
            break;
            
        default:
            post("invalid SVM type, send a 'help' message to the first inlet for available types");
            break;
    }
}

void ml_svm::set_kernel(int kernel)
{
    switch (kernel)
    {
        case GRT::LINEAR:
        case GRT::POLY:
        case GRT::RBF:
        case GRT::SIGMOID:
        case GRT::PRECOMPUTED:
//            param.kernel_type = kernel;
            break;
            
        default:
            post("invalid kernel type, send a 'help' message to the first inlet for available types");
            break;
    }
}

void ml_svm::set_degree(int degree)
{
//    param.degree = degree;
}

void ml_svm::set_gamma(float gamma)
{
//    param.gamma = (double)gamma;
}

void ml_svm::set_coef0(float coef0)
{
    // param.coef0 = (double)coef0;
}

void ml_svm::set_cost(float cost)
{
    // param.C = (double)cost;
}

void ml_svm::set_nu(float nu)
{
    // param.nu = (double)nu;
}

void ml_svm::set_epsilon(float epsilon)
{
    // param.eps = (double)epsilon;
}

void ml_svm::set_cachesize(int cachesize)
{
    // param.cache_size = cachesize;
}

void ml_svm::set_shrinking(int shrinking)
{
    switch (shrinking)
    {
        case 0:
        case 1:
            // param.shrinking = shrinking;
            break;
            
        default:
            error("shrinking must either be 0 (off) or 1 (on)");
            break;
    }
}

void ml_svm::set_estimates(bool estimates)
{
    this->estimates = estimates;
}

void ml_svm::set_weights(const AtomList &weights)
{
    // param.nr_weight = weights.Count();
//    weight_labels.clear();
//    weight_values.clear();
//    
//    for (int count = 0; count < param.nr_weight; ++count)
//    {
//        std::string weight = GetString(GetSymbol(weights[count]));
//        std::string::size_type location = weight.find(weight_delimiter);
//        
//        if (location == std::string::npos)
//        {
//            error("no ':' found, weights must be a list of class:weight pairs");
//            return;
//        }
//        
//        std::string::size_type weight_length = weight.length();
//        std::string::size_type value_length = weight_length - location - 1;
//        
//        std::string value_s = weight.substr(location + 1, value_length);
//        std::string weight_s = weight.substr(0, location);
//        
//        int label = atoi(weight_s.c_str());
//        double value = atof(value_s.c_str());
//        
//        weight_labels.push_back(label);
//        weight_values.push_back(value);
//    }
}

void ml_svm::set_mode(int mode)
{
    if (mode < 2)
    {
        error("n-fold cross validation: n must >= 2");
        return;
    }
    nr_fold = mode;
}

// Attribute getters
void ml_svm::get_type(int &type) const
{
//    type = param.svm_type;
}

void ml_svm::get_kernel(int &kernel) const
{
//    kernel = param.kernel_type;
}

void ml_svm::get_degree(int &degree) const
{
//    degree = param.degree;
}

void ml_svm::get_gamma(float &gamma) const
{
//    gamma = param.gamma;
}

void ml_svm::get_coef0(float &coef0) const
{
//    coef0 = param.coef0;
}

void ml_svm::get_cost(float &cost) const
{
//    cost = param.C;
}

void ml_svm::get_nu(float &nu) const
{
//    nu = param.nu;
}

void ml_svm::get_epsilon(float &epsilon) const
{
//    epsilon = param.eps;
}

void ml_svm::get_cachesize(int &cachesize) const
{
//    cachesize = param.cache_size;
}

void ml_svm::get_shrinking(int &shrinking) const
{
//    shrinking = param.shrinking;
}

void ml_svm::get_estimates(bool &estimates) const
{
//    estimates = this->estimates;
}

void ml_svm::get_weights(AtomList &weights) const
{
//    uint32_t num_weights = weight_labels.size();
//    
//    for (uint32_t count = 0; count < num_weights; ++count)
//    {
//        int weight_label = weight_labels[count];
//        double weight_value = weight_values[count];
//        
//        std::stringstream weight;
//        weight << weight_label << ":" << weight_value;
//        const char *weight_c = weight.str().c_str();
//        const t_symbol *weight_s = MakeSymbol(weight_c);
//        t_atom weight_a;
//        SetSymbol(weight_a, weight_s);
//        
//        weights.Append(weight_a);
//    }
}

void ml_svm::get_mode(int &mode) const
{
    mode = nr_fold;
}

// Methods

void ml_svm::save(const t_symbol *path) const
{
//    t_atom status;
//    int rv = -1;
//    const char *path_s = GetString(path);
//    
//    SetBool(status, true);
//    
//    if (model != NULL)
//    {
//        rv = svm_save_model(path_s, model);
//    }
//    
//    if (rv == -1)
//    {
//        error("an error occurred saving the model, ensure a model has been created with 'train'");
//        SetBool(status, false);
//    }
//    
//    ToOutAnything(1, s_saved, 1, &status);
}

void ml_svm::load(const t_symbol *path)
{
//    t_atom status;
//    const char *path_s = GetString(path);
//    model = svm_load_model(path_s);
//    
//    SetBool(status, true);
//    
//    if (model == NULL)
//    {
//        error("unable to load model");
//        SetBool(status, false);
//    }
//
//    ToOutAnything(1, s_loaded, 1, &status);
}

void ml_svm::cross_validation()
{
//    int i;
//    int total_correct = 0;
//    double total_error = 0;
//    double sumv = 0, sumy = 0, sumvv = 0, sumyy = 0, sumvy = 0;
//    double *target = NULL;
//    
//    copy_observations_to_problem(prob, observations);
//    const char *error_message = svm_check_parameter(&prob, &param);
//    
//    if (error_message != NULL)
//    {
//        error("%s", error_message);
//    }
//    
//    target = (double *)malloc(prob.l * sizeof(prob.l));
//    svm_cross_validation(&prob, &param, nr_fold, target);
//    
//    if(param.svm_type == EPSILON_SVR ||
//       param.svm_type == NU_SVR)
//    {
//        for(i=0;i<prob.l;i++)
//        {
//            double y = prob.y[i];
//            double v = target[i];
//            total_error += (v-y)*(v-y);
//            sumv += v;
//            sumy += y;
//            sumvv += v*v;
//            sumyy += y*y;
//            sumvy += v*y;
//        }
//        post("cross validation mean squared error = %g\n",total_error/prob.l);
//        post("cross validation squared correlation coefficient = %g\n",
//             ((prob.l * sumvy - sumv * sumy) * (prob.l * sumvy - sumv * sumy))/
//             ((prob.l * sumvv - sumv * sumv) * (prob.l * sumyy - sumy * sumy))
//             );
//    }
//    else
//    {
//        for(i = 0; i < prob.l; i++)
//        {
//            if(target[i] == prob.y[i])
//            {
//                ++total_correct;
//            }
//        }
//        post("cross validation accuracy = %g%%\n", 100.0 * total_correct / prob.l);
//    }
//    free(target);
//    free_problem_data(&prob);
    
}

void ml_svm::train()
{
//    free_problem_data(&prob);
//    svm_free_and_destroy_model(&model);
//    
//    prob.l = observations.size();
//    
//    if (prob.l == 0)
//    {
//        error("no observations added, use 'add' to add labeled feature vectors");
//        return;
//    }
//    
//    copy_observations_to_problem(prob, observations);
//    feature_map::size_type max_index = get_observations_max_index(observations);
//    
//    if(param.gamma == 0 && max_index > 0)
//    {
//        param.gamma = 1.0 / (float)max_index;
//    }
//    
//    if(param.kernel_type == PRECOMPUTED)
//    {
//        for(int32_t i = 0; i < prob.l; ++i)
//        {
//            if (prob.x[i][0].index != 0)
//            {
//                error("wrong input format: first column must be 0:sample_serial_number\n");
//                return;
//            }
//            if ((int)prob.x[i][0].value <= 0 || (uint32_t)prob.x[i][0].value > max_index)
//            {
//                error("wrong input format: sample_serial_number out of range\n");
//                return;
//            }
//        }
//    }
//    
//    const char *error_message = svm_check_parameter(&prob, &param);
//    
//    if (error_message != NULL)
//    {
//        error("%s", error_message);
//    }
//    
//    model = svm_train(&prob, &param);
//    
//    t_atom a_num_sv;
//    t_atom a_num_classes;
//    
//    AtomList result;
//    
//    SetInt(a_num_sv, -1);
//    SetInt(a_num_classes, -1);
//    
//    if (model == NULL)
//    {
//        error("training model failed");
//    }
//    else
//    {
//        SetInt(a_num_sv, svm_get_nr_sv(model));
//        SetInt(a_num_classes, svm_get_nr_class(model));
//    }
//    
//    result.Append(a_num_classes);
//    result.Append(a_num_sv);
//    
//    ToOutAnything(1, s_train, result);
    // NOTE: don't free problem here because "svm_model contains pointers to svm_problem"
}

void ml_svm::clear()
{
//    prob.l = 0;
//    
//    free_problem_data(&prob);
//    svm_free_and_destroy_model(&model);
//    
//    ml_base::clear();
}

void ml_svm::classify(int argc, const t_atom *argv)
{
//    if (model == NULL)
//    {
//        error("no model");
//        return;
//    }
//    
//    uint32_t num_features = argc;
//    uint32_t max_index = num_features + 1;
//    int svm_type = svm_get_svm_type(model);
//    int nr_class = svm_get_nr_class(model);
//    double *prob_estimates=NULL;
//    std::vector<int> labels;
//    std::vector<double> probabilities;
//    AtomList estimates;
//    
//    double classification = 0.0;
//    
//    svm_node *nodes = (svm_node *)malloc(max_index * sizeof(svm_node));
//    
//    for (uint32_t index = 0; index < num_features; ++index)
//    {
//        nodes[index].index = index + 1;
//        double value = GetAFloat(argv[index]);
//        
//        nodes[index].value = value;
//    }
//    
//    nodes[num_features].index = -1;
//    nodes[num_features].value = 0.0;
//    
//    if(this->estimates)
//    {
//        if(svm_check_probability_model(model) == 0)
//        {
//            error("probability attribute set to 1, but model doesn't support probability");
//        }
//        else
//        {
//            t_atom estimates_a;
//            SetSymbol(estimates_a, s_estimates);
//            estimates.Append(estimates_a);
//            
//            if (svm_type == NU_SVR || svm_type == EPSILON_SVR)
//            {
//                post("probability model for test data: target value = predicted value + z,\nz: Laplace distribution e^(-|z|/sigma)/(2sigma),sigma=%g\n", svm_get_svr_probability(model));
//            }
//            else
//            {
//                int *labels_ = (int *)malloc(nr_class * sizeof(int));
//                svm_get_labels(model, labels_);
//                
//                for(int32_t j = 0; j < nr_class; ++j)
//                {
//                    labels.push_back(labels_[j]);
//                }
//                free(labels_);
//            }
//            
//            if ((svm_type == C_SVC || svm_type == NU_SVC))
//            {
//                prob_estimates = (double *)malloc(nr_class * sizeof(double));
//                classification = svm_predict_probability(model, nodes, prob_estimates);
//                
//                for(int32_t j = 0; j < nr_class; ++j)
//                {
//                    probabilities.push_back(prob_estimates[j]);
//                }
//            }
//            
//            for (int32_t j = 0; j < nr_class; ++j)
//            {
//                t_atom label_a;
//                t_atom probability_a;
//                
//                // Need to call SetDouble() first or label_a gets corrupted. Bug in Flext?
//                SetDouble(&probability_a, probabilities[j]);
//                SetInt(label_a, labels[j]);
//                
//                estimates.Append(label_a);
//                estimates.Append(probability_a);
//            }
//            
//            ToOutList(1, estimates);
//        }
//    }
//    else
//    {
//        classification = svm_predict(model, nodes);
//    }
//    
//    free(nodes);
//    ToOutFloat(0, (float)classification);
}

void ml_svm::usage()
{
//    post("%s", ML_POST_SEP);
//    post("Attributes:");
//    post("%s", ML_POST_SEP);
//    post("type:\tset type of SVM (default 0)");
//    post("	0 -- C-SVC		(multi-class classification)");
//    post("	1 -- nu-SVC		(multi-class classification)");
//    post("	2 -- one-class SVM");
//    post("	3 -- epsilon-SVR	(regression)");
//    post("	4 -- nu-SVR		(regression)");
//    post("kernel:\tset type of kernel function (default 2)");
//    post("	0 -- linear: u'*v");
//    post("	1 -- polynomial: (gamma*u'*v + coef0)^degree");
//    post("	2 -- radial basis function: exp(-gamma*|u-v|^2)");
//    post("	3 -- sigmoid: tanh(gamma*u'*v + coef0)");
//    post("	4 -- precomputed kernel (kernel values in training_set_file)");
//    post("degree:\tset degree in kernel function (default 3)");
//    post("gamma:\tset gamma in kernel function (default 1/num_features)");
//    post("coef0:\tset coef0 in kernel function (default 0)");
//    post("cost:\tset the parameter C of C-SVC, epsilon-SVR, and nu-SVR (default 1)");
//    post("nu:\tset the parameter nu of nu-SVC, one-class SVM, and nu-SVR (default 0.5)");
//    post("epsilon:\tset the epsilon in loss function of epsilon-SVR (default 0.1)");
//    post("cachesize:\tset cache memory size in MB (default 100)");
//    post("epsilon:\tset tolerance of termination criterion (default 0.001)");
//    post("shrinking:\twhether to use the shrinking heuristics, 0 or 1 (default 1)");
//    post("estimates:\twhether to train a SVC or SVR model for probability estimates, 0 or 1 (default 0)");
//    post("weights:\tlist of weight tuples 'class:weight' to set the parameter of class to weight*C, for C-SVC (default 1)");
//    post("n:\tn-fold cross validation mode");
//    post("%s", ML_POST_SEP);
//    post("Methods:");
//    post("%s", ML_POST_SEP);
//    post("add:\tlist comprising a class id followed by n features; <class> <feature 1> <feature 2> etc");
//    post("save:\tsave a trained model, first argument gives path to save location");
//    post("load:\tload a trained model, first argument gives path to the load location");
//    post("cross_validation:\t\tperform cross-validation");
//    post("train:\ttrain the SVM based on labelled vectors added with 'add'");
//    post("clear:\tclear the stored training data");
//    post("classify:\tgive the class of the input feature vector provided as a list");
//    post("help:\tpost this usage statement to the console");
//    post("%s", ML_POST_SEP);
    
}

FLEXT_LIB("ml.svm", ml_svm);
    
} //namespace ml

