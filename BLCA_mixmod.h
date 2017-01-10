/*Functions for the fitting of Latent Class Analysis models using MCMC
	methods. Two implementations of the model are included in the Bayesian
	formulation: collapsed and not collapsed.
	
	Author:	Jason Wyse,
			School of Computer Science and Statistics,
			Lloyd Institute,
			Trinity College,
			Dublin 2,
			Ireland.
			mailto: wyseja@tcd.ie
			
	Last modification of this code: Mon 09 May 2016 15:38:03 IST   */

#ifndef __BLCA_MIXMOD_H__
#define __BLCA_MIXMOD_H__

#include "BLCA_required_libs.h"
#include "BLCA_utils.h"

struct component
{
	int in_use; /*indicator saying whether the component is in use or not*/
	
	int n_g; /*number of members of component*/
	
	//int *indexes_g; /*indexes of members of component in Y (row-wise)*/
	
	int **N; /*gives the number in category k of variable j*/
	
	double **prob_variables; /*matrix of variable probabilities*/
	
	double log_prob; /*quantity that can be updated to save computations*/

};

struct mix_mod
/*structure to hold mixture essentials*/
{
	int collapsed; /*logical indicating collapsed model or not*/

	int G; /*total number of groups*/
	
	int n; /*total number of data*/
	
	int n_gibbs; /*number of data pts to update in Gibbs*/
	
	int d; /*total number of variables recorded*/
	
	int maxgroups;
	
	int *ncat; /*number of categories for each of the variables*/
	
	int *varindicator; /*indicates whether the variable is in or not*/
	
	int **Y; /*the raw data stacked as variable \times obs (J \times N)*/
	
	int **Yobs; /*a second copy of the raw data stacked as obs \times variable */
	
	/*two copies of the data are stored as I think its better for memory access
		- we can use one or the other depending on the calculation to be carried out*/
	
	int *z; /*group memberhsip indicator*/
	
	double **s; /*group probability membership*/
	
	int *whereis; /*stores the index in components of a component*/

	struct component **components; /*pointer to array of pointers to components*/
	
	struct component *undiscriminating; /*for variable selection: pointer to component for 
														undiscriminating variables*/
	
	/*other hyperparameters*/
	
	double alpha; /*alpha: dirichlet prior on weights symmetric*/
	
	double beta; /*delta: dirichlet prior on the category probabilities symmetric*/
	
	double prior_prob_variable_include; /*prior probability of inclusion of any of the variables*/ 
	
	double *log_prior_G; /*this is the prior for the number of groups... poisson(1)*/
							
	double *table_a; /*this is a lookup table for the values of a when ejecting or
								absorbing components*/
	
	double *weights; /*component weights if collapsed = FALSE*/
	
	int hprior_model; /*logical: sample a hyperprior on the probability of variable inclusion*/
	
	double hprior_model_a0; /*hyperparameter values for the Beta hyperprior if hprior_model == TRUE*/
	
	double hprior_model_b0;
	
	double log_like;
	
	FILE *fp_log; /*file pointer for the debugger log*/
	
	int EM_fit ;
	
	int EM_MAP; /*find the map in an EM fit?*/ 

};

#include "BLCA_component.h"
#include "BLCA_initialize.h"
#include "BLCA_results.h"
#include "BLCA_post_hoc.h"
#include "BLCA_label_updates.h"
#include "BLCA_eject_absorb.h"
#include "BLCA_variable_selection.h"
#include "BLCA_density.h"
#include "BLCA_analysis.h"


struct mix_mod *BLCA_allocate_mixmod(int datasize, int datadimension, int maxgroups, int initgroups,double *prior_hparams,int *ncat, int collapsed, int EM_fit, int EM_MAP) ;

void BLCA_free_mixmod(struct mix_mod *mixmod) ;

#endif